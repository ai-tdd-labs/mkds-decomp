#!/usr/bin/env python3
"""permute2.py — register-pressure permuter for the near-miss tail.

The old permute.py only reordered declarations; measurements showed that never
reaches the register-allocation floor. This one applies AGGRESSIVE, possibly
semantics-bending textual mutations — safe because the byte-oracle is the
verifier: a variant only "wins" when it byte-matches the ROM exactly, and then
it is BY DEFINITION the right code. Non-matching variants are discarded.

v3 upgrades (trick-book uit ai/tricks.jsonl + sm64ds notes/mwccarm-codegen.md):
  * pluggable oracle:  --oracle mkds (default, aimatch/wibo)
                       --oracle sm64ds (shim naar ../sm64ds-decomp match-keten)
  * trick-operatoren:  volatile_local, counter_narrow, ptr_index, uchar_flip,
                       global_reload, pragma_size, do_while
  * symptoom-matcher:  disassembleert de diff van de beste kandidaat en weegt
                       de mutatie-keuze naar het herkende symptoom
                       (regalloc -> decl/temp/volatile, ldrb/ldrsb -> uchar,
                        mvn -> ptr_index, predicated-vs-branch -> arm_swap, ...)

Mutations per iteration (1..3 picks, symptoom-gewogen):
  decl_swap   : swap two adjacent local-declaration lines (recolors callee-saved)
  stmt_swap   : swap two adjacent statements in one block (scheduling jitter)
  temp_in     : hoist a call/deref argument into a fresh temp local
  temp_out    : inline a single-use `T x = EXPR;` temp
  cast_jitter : add/remove (int)/(u32)/(u8)/(s16) casts on simple operands
  cond_flip   : negate an if-condition and swap its arms
  type_jitter : flip a local's type int<->u32<->s32
  incr_move   : move `i++` between loop head and body tail
  volatile_local : T x = ...  ->  T volatile x = ...   (forceert stack-spill)
  counter_narrow : int i      ->  unsigned short i     (lsls/lsrs #16 wrap)
  ptr_index   : a[b] -> *(a + (b))                     (vermijdt mvn-materialisatie)
  uchar_flip  : (char*/s8) <-> (unsigned char*/u8)     (ldrsb <-> ldrb)
  global_reload : gebruik data_X direct i.p.v. lokale kopie (dubbele load)
  pragma_size : #pragma optimize_for_size aan/uit      (branch- vs predicated-vorm)
  do_while    : for(...)  ->  init; if(c){do{..}while(c);}  (lus zonder dubbele guard)

Hill-climb with random restarts; score = oracle mismatch count.

  tools/permute2.py --func NAME [--src ai/scratch/agent_X.c] [--iters 600] [--seed N]
  tools/permute2.py --oracle sm64ds --func func_ovNNN_... --src cand.c --iters 120
"""
import argparse
import collections
import os
import pathlib
import random
import re
import sys
import tempfile

os.environ.setdefault("MKDS_CC", "wibo")
MKDS = pathlib.Path(__file__).resolve().parent.parent
sys.path.insert(0, str(MKDS / "tools"))

O = None  # oracle-module; gezet in main() via --oracle

DECL_RE = re.compile(r"^\s+(?:unsigned |signed |const )*(?:void|int|char|short|long|u8|u16|u32|s8|s16|s32|fx32)\b[^;()]*;\s*$")
STMT_RE = re.compile(r"^\s+\S.*;\s*$")


def lines_of(txt):
    return txt.split("\n")


def _decl_name(l):
    m = re.match(r"^\s+(?:unsigned |signed |const )*\w+\s*\**\s*(\w+)", l)
    return m.group(1) if m else None


def m_decl_swap(rng, L):
    def safe(i):
        a, b = _decl_name(L[i]), _decl_name(L[i + 1])
        # niet wisselen als de één de ander in z'n initializer gebruikt
        return not (a and re.search(rf"\b{a}\b", L[i + 1].split("=", 1)[-1])) \
           and not (b and re.search(rf"\b{b}\b", L[i].split("=", 1)[-1]))
    idx = [i for i in range(len(L) - 1)
           if DECL_RE.match(L[i]) and DECL_RE.match(L[i + 1]) and safe(i)]
    if not idx: return None
    i = rng.choice(idx); L = L[:]; L[i], L[i + 1] = L[i + 1], L[i]; return L


INIT_DECL_RE = re.compile(
    r"^\s+(?:unsigned |signed |const )*(?:void|int|char|short|long|u8|u16|u32|s8|s16|s32|fx32)\b[^;=]*=\s")


def m_stmt_swap(rng, L):
    # NB: decl-met-initializer (`int x = f();`) nooit verplaatsen — een use kan
    # er dan vóór komen te staan (undefined identifier; zie lakmoes-run 2026-07-19)
    idx = [i for i in range(len(L) - 1)
           if STMT_RE.match(L[i]) and STMT_RE.match(L[i + 1])
           and not DECL_RE.match(L[i]) and not DECL_RE.match(L[i + 1])
           and not INIT_DECL_RE.match(L[i]) and not INIT_DECL_RE.match(L[i + 1])
           and "{" not in L[i] + L[i + 1] and "}" not in L[i] + L[i + 1]
           and "return" not in L[i] + L[i + 1]]
    if not idx: return None
    i = rng.choice(idx); L = L[:]; L[i], L[i + 1] = L[i + 1], L[i]; return L


def m_temp_in(rng, L):
    # X = A->b[.c]; style RHS hoisted through a temp
    idx = [i for i, l in enumerate(L) if re.match(r"^(\s+)([\w\[\]\.\->]+)\s*=\s*([^;{}]+);\s*$", l)
           and "(" not in l]
    if not idx: return None
    i = rng.choice(idx)
    m = re.match(r"^(\s+)([\w\[\]\.\->]+)\s*=\s*([^;{}]+);\s*$", L[i])
    ind, lhs, rhs = m.groups()
    t = f"_t{rng.randrange(100)}"
    L = L[:]; L[i] = f"{ind}{{ int {t} = (int)({rhs}); {lhs} = {t}; }}"
    return L


def m_temp_out(rng, L):
    # inline single-use `int x = EXPR;`
    for i, l in enumerate(L):
        m = re.match(r"^\s+(?:int|u32|s32)\s+(\w+)\s*=\s*([^;]+);\s*$", l)
        if not m: continue
        name, expr = m.groups()
        uses = [j for j, l2 in enumerate(L) if j != i and re.search(rf"\b{name}\b", l2)]
        if len(uses) == 1 and rng.random() < 0.7:
            L = L[:]
            L[uses[0]] = re.sub(rf"\b{name}\b", f"({expr})", L[uses[0]])
            L[i] = ""
            return L
    return None


CASTS = ["(int)", "(u32)", "(s32)", "(u8)", "(s16)"]


def m_cast_jitter(rng, L):
    idx = [i for i, l in enumerate(L) if "=" in l and ";" in l and "==" not in l]
    if not idx: return None
    i = rng.choice(idx); L = L[:]
    if rng.random() < 0.5:
        # strip één bestaande cast
        L[i] = re.sub(r"\((?:int|u32|s32|u8|s16)\)", "", L[i], count=1)
    else:
        m = re.search(r"=\s*", L[i])
        if not m: return None
        avail = _avail_types(L)
        opts = [c for c in CASTS if c.strip("()") in avail or c == "(int)"]
        if not opts: return None
        c = rng.choice(opts)
        L[i] = L[i][:m.end()] + c + L[i][m.end():]
    return L


def m_cond_flip(rng, L):
    idx = [i for i, l in enumerate(L) if re.search(r"\bif\s*\(", l) and "else" not in l]
    if not idx: return None
    i = rng.choice(idx); L = L[:]
    L[i] = re.sub(r"if\s*\((.*)\)", lambda m: f"if (!({m.group(1)}))", L[i], count=1)
    return L


def _avail_types(L):
    """alleen typen gebruiken die het bestand zelf kent — een u32 in een bron
    zonder typedef parseert als expressie en maakt alles 'undefined'
    (gevonden in de sm64ds-lakmoesrun 2026-07-19)."""
    txt = "\n".join(L)
    out = ["int", "unsigned int"]
    for t in ("u32", "s32", "u16", "s16", "u8", "s8"):
        if re.search(rf"\b{t}\b", txt):
            out.append(t)
    return out


def m_type_jitter(rng, L):
    idx = [i for i, l in enumerate(L) if re.match(r"^\s+(int|u32|s32)\s+\w+", l)]
    if not idx: return None
    i = rng.choice(idx); L = L[:]
    cur = re.match(r"^\s+(int|u32|s32)", L[i]).group(1)
    opts = [t for t in _avail_types(L) if t != cur and t in ("int", "u32", "s32", "unsigned int")]
    if not opts: return None
    new = rng.choice(opts)
    L[i] = re.sub(rf"^(\s+){cur}\b", rf"\g<1>{new}", L[i], count=1)
    return L


def m_incr_move(rng, L):
    for i, l in enumerate(L):
        m = re.match(r"^(\s+)for\s*\((.*);(.*);\s*(\w+)\+\+\s*\)\s*{\s*$", l)
        if m:
            ind, init, cond, var = m.groups()
            # vind sluit-accolade van dit blok (simpel: eerstvolgende regel met alleen })
            for j in range(i + 1, len(L)):
                if L[j].strip() == "}":
                    L = L[:]
                    L[i] = f"{ind}for ({init};{cond}; ) {{"
                    L.insert(j, f"{ind}    {var}++;")
                    return L
    return None


# ---- trick-operatoren (uit ai/tricks.jsonl + sm64ds mwccarm-codegen.md) -----

LOCAL_DECL_RE = re.compile(
    r"^(\s+)((?:unsigned |signed )?(?:int|char|short|long|u8|u16|u32|s8|s16|s32)\s*\*?)\s+(\w+)\s*=")


def m_volatile_local(rng, L):
    """tricks.jsonl: 'volatile-local forceert stack-spill + herlaad (str/ldr [sp])'."""
    idx = [i for i, l in enumerate(L) if LOCAL_DECL_RE.match(l) and "volatile" not in l]
    if not idx: return None
    i = rng.choice(idx); L = L[:]
    m = LOCAL_DECL_RE.match(L[i])
    L[i] = L[i][:m.end(2)] + " volatile" + L[i][m.end(2):]
    return L


def m_counter_narrow(rng, L):
    """tricks.jsonl: 'u16-loopteller — lsls/lsrs #16 rond de teller = 16-bit wrap'."""
    idx = [i for i, l in enumerate(L) if re.match(r"^\s+int\s+[ijk]\w{0,3}\s*[;=]", l)]
    if not idx: return None
    i = rng.choice(idx); L = L[:]
    L[i] = re.sub(r"^(\s+)int\b", r"\1unsigned short", L[i], count=1)
    return L


def m_ptr_index(rng, L):
    """tricks.jsonl: '*(p-1-i) i.p.v. p[-1-i] — p[-1-i] materialiseert -1-i met extra mvns'."""
    cands = []
    for i, l in enumerate(L):
        for m in re.finditer(r"\b(\w+)\[([^\[\]]+)\]", l):
            if m.group(1) in ("if", "while", "for"): continue
            cands.append((i, m.span(), m.group(1), m.group(2)))
    if not cands: return None
    i, (a, b), name, expr = rng.choice(cands)
    L = L[:]
    L[i] = L[i][:a] + f"*({name} + ({expr}))" + L[i][b:]
    return L


def m_uchar_flip(rng, L):
    """tricks.jsonl: 'ldrb vs ldrsb — -char signed maakt char-deref ldrsb; unsigned-cast -> ldrb'."""
    subs = [(r"\(char\s*\*\)", "(unsigned char *)"), (r"\(unsigned char\s*\*\)", "(char *)"),
            (r"\(s8\)", "(u8)"), (r"\(u8\)", "(s8)"),
            (r"\(signed char\s*\*\)", "(unsigned char *)")]
    idx = [(i, p, r) for i, l in enumerate(L) for p, r in subs if re.search(p, l)]
    if not idx: return None
    i, p, r = rng.choice(idx); L = L[:]
    L[i] = re.sub(p, r, L[i], count=1)
    return L


def m_global_reload(rng, L):
    """tricks.jsonl: 'herlaad via de globale i.p.v. lokale var — gebruik data_X direct'."""
    for i, l in enumerate(L):
        m = re.match(r"^\s+\w[\w \*]*\s(\w+)\s*=\s*(&?data_\w+)\s*;", l)
        if not m: continue
        name, g = m.groups()
        uses = [j for j, l2 in enumerate(L) if j != i and re.search(rf"\b{name}\b", l2)]
        if len(uses) >= 2:
            j = rng.choice(uses); L = L[:]
            L[j] = re.sub(rf"\b{name}\b", g, L[j], count=1)
            return L
    return None


PRAGMA = "#pragma optimize_for_size on"


def m_pragma_size(rng, L):
    """tricks.jsonl: 'optimize_for_size — gedeelde epiloog i.p.v. gepredikeerde instructies'."""
    L = L[:]
    if any(PRAGMA in l for l in L):
        return [l for l in L if PRAGMA not in l]
    # vlak vóór de eerste functie-definitie invoegen
    for i, l in enumerate(L):
        if re.match(r"^\w[\w \*]*\s+\w+\s*\([^;]*\)\s*{?\s*$", l) and "extern" not in l:
            L.insert(i, PRAGMA)
            return L
    return None


def m_do_while(rng, L):
    """tricks.jsonl: 'do/while achter if i.p.v. for — lus zonder dubbele guard'."""
    txt = "\n".join(L)
    for m in re.finditer(r"(^\s*)for\s*\(([^;]*);([^;]*);([^)]*)\)\s*{", txt, re.M):
        open_i = txt.find("{", m.end() - 1)
        close_i = _find_block(txt, open_i)
        if close_i < 0: continue
        ind, init, cond, inc = m.group(1), m.group(2).strip(), m.group(3).strip(), m.group(4).strip()
        if not cond: continue
        body = txt[open_i + 1:close_i]
        init_s = f"{init}; " if init else ""
        inc_s = f" {inc};" if inc else ""
        new = (txt[:m.start()] + f"{ind}{init_s}if ({cond}) {{ do {{{body}{inc_s}}} while ({cond}); }}"
               + txt[close_i + 1:])
        return lines_of(new)
    return None


# ---- blok-niveau mutaties (geleerd van agent-kraken; zie ai/tricks.jsonl) ----

def _find_block(txt, open_idx):
    """index van de sluit-accolade die hoort bij txt[open_idx]=='{'."""
    depth = 0
    for i in range(open_idx, len(txt)):
        if txt[i] == "{": depth += 1
        elif txt[i] == "}":
            depth -= 1
            if depth == 0: return i
    return -1


IF_RE = re.compile(r"\bif\s*\(")


def _if_blocks(txt):
    """(cond_start, then_open, then_close, else_open, else_close) per if."""
    out = []
    for m in IF_RE.finditer(txt):
        cp = txt.find("(", m.end() - 1)
        depth = 0; ce = -1
        for i in range(cp, len(txt)):
            if txt[i] == "(": depth += 1
            elif txt[i] == ")":
                depth -= 1
                if depth == 0: ce = i; break
        if ce < 0: continue
        to = txt.find("{", ce)
        if to < 0 or txt[ce + 1:to].strip(): continue
        tc = _find_block(txt, to)
        if tc < 0: continue
        rest = txt[tc + 1:tc + 16]
        eo = ec = -1
        em = re.match(r"\s*else\s*{", rest)
        if em:
            eo = tc + 1 + em.end() - 1
            ec = _find_block(txt, eo)
        out.append((m.start(), cp, ce, to, tc, eo, ec))
    return out


def m_arm_swap(rng, L):
    """K3/Fable-truc: grote arm als THEN — flip conditie + wissel armen (blok-niveau)."""
    txt = "\n".join(L)
    cands = [b for b in _if_blocks(txt) if b[5] >= 0]
    if not cands: return None
    s, cp, ce, to, tc, eo, ec = rng.choice(cands)
    cond = txt[cp + 1:ce]; then_b = txt[to + 1:tc]; else_b = txt[eo + 1:ec]
    new = txt[:s] + f"if (!({cond})) {{{else_b}}} else {{{then_b}}}" + txt[ec + 1:]
    return lines_of(new)


def m_nest_next(rng, L):
    """K3-truc: het if/else-blok dat direct NA een blok komt, erbinnen nesten."""
    txt = "\n".join(L)
    blocks = _if_blocks(txt)
    if len(blocks) < 2: return None
    for a, b in zip(blocks, blocks[1:]):
        end_a = a[6] if a[5] >= 0 else a[4]      # einde (incl. else) van blok A
        if b[0] <= end_a:                         # B genest IN A -> negatieve slice
            continue                              #   zou vals als "lege gap" slagen
        gap = txt[end_a + 1:b[0]]
        if gap.strip() == "":                     # B volgt direct op A
            end_b = b[6] if b[5] >= 0 else b[4]
            piece = txt[b[0]:end_b + 1]
            # verplaats B naar binnen, vlak voor de sluit-accolade van A's then-blok
            ins = a[4]
            new = txt[:ins] + piece + "\n" + txt[ins:b[0]] + txt[end_b + 1:]
            return lines_of(new)
    return None


def m_tail_dup(rng, L):
    """tail-statement NA if/else dupliceren in beide armen (aparte epilogen)."""
    txt = "\n".join(L)
    for s, cp, ce, to, tc, eo, ec in _if_blocks(txt):
        if eo < 0: continue
        m = re.match(r"\s*\n(\s*)([^\n{};]+;)\s*\n", txt[ec + 1:])
        if not m: continue
        stmt = m.group(2)
        new = (txt[:tc] + "    " + stmt + "\n" + txt[tc:ec] + "    " + stmt + "\n"
               + txt[ec:ec + 1] + txt[ec + 1 + m.end():])
        return lines_of(new)
    return None


MUTS = [m_decl_swap, m_stmt_swap, m_temp_in, m_temp_out, m_cast_jitter,
        m_cond_flip, m_type_jitter, m_incr_move,
        m_arm_swap, m_arm_swap, m_nest_next, m_nest_next, m_tail_dup,
        m_volatile_local, m_counter_narrow, m_ptr_index, m_uchar_flip,
        m_global_reload, m_pragma_size, m_do_while]


# ---- symptoom-matcher: diff-diagnose -> gewogen mutatie-keuze ---------------
# In plaats van blind gokken: disassembleer de mismatches van de beste
# kandidaat, herken het symptoom, en geef de bijpassende remedie extra gewicht.
# Symptoomtaal = de nm-categorieën (register allocation / predicate-vs-branch /
# base materialization / ...) uit de opgebouwde kennisbank.

SYMPTOM_MUTS = {
    "regalloc":    [m_decl_swap, m_temp_in, m_temp_out, m_stmt_swap,
                    m_volatile_local, m_global_reload],
    "sign_byte":   [m_uchar_flip],
    "sign_half":   [m_cast_jitter],
    "mvn":         [m_ptr_index],
    "pred_branch": [m_arm_swap, m_cond_flip, m_nest_next, m_tail_dup, m_pragma_size],
    "narrow16":    [m_counter_narrow, m_cast_jitter],
    "spill":       [m_volatile_local, m_temp_in],
    "sched":       [m_stmt_swap, m_do_while, m_temp_in, m_temp_out],
}


def diagnose(target, code, relocs, mode):
    """Counter van symptomen over de mismatch-instructies."""
    from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB
    md = Cs(CS_ARCH_ARM, CS_MODE_THUMB if mode == "thumb" else CS_MODE_ARM)

    def dis(data):
        return {i.address: (i.mnemonic, i.op_str) for i in md.disasm(data, 0)}

    td, cd = dis(target), dis(code)
    wc = set()
    for off in relocs:
        wc.update({off, off + 2})
    syms = collections.Counter(); seen = set()
    for off in range(0, min(len(target), len(code)), 2):
        if off in wc or target[off:off + 2] == code[off:off + 2]:
            continue
        io = off & ~1 if mode == "thumb" else off & ~3
        if io in seen: continue
        seen.add(io)
        t, c = td.get(io), cd.get(io)
        if not t or not c:
            syms["sched"] += 1; continue
        (tm, to), (cm, co) = t, c
        if {tm, cm} == {"ldrb", "ldrsb"}: syms["sign_byte"] += 1
        elif {tm, cm} == {"ldrh", "ldrsh"}: syms["sign_half"] += 1
        elif "mvn" in (tm, cm): syms["mvn"] += 1
        elif ("[sp" in to) != ("[sp" in co): syms["spill"] += 1
        elif (("lsl" in tm or "lsr" in tm or "lsl" in cm or "lsr" in cm)
              and "#16" in to + co): syms["narrow16"] += 1
        elif tm.startswith("b") != cm.startswith("b"): syms["pred_branch"] += 1
        elif tm == cm and to != co: syms["regalloc"] += 1
        elif tm != cm and tm.rstrip("eqnecsccmiplvshilogeltgtle") == \
                cm.rstrip("eqnecsccmiplvshilogeltgtle"): syms["pred_branch"] += 1
        else: syms["sched"] += 1
    return syms


def weighted_pool(syms):
    """basis-MUTS + symptoom-remedies, gewogen naar hoe vaak het symptoom optreedt."""
    pool = list(MUTS)
    for s, n in syms.items():
        pool += SYMPTOM_MUTS.get(s, []) * (2 * min(n, 4))
    return pool


_LOCAL_NAME_RE = re.compile(
    r"^\s+(?:unsigned |signed |const |volatile )*"
    r"(?:void|int|char|short|long|u8|u16|u32|s8|s16|s32|fx32)\s*\**\s*(\w+)\s*[;=]", re.M)


def scope_ok(txt):
    """goedkope pre-check: elke lokale declaratie moet vóór het eerste gebruik
    staan — blok-verplaatsers (nest_next e.d.) kunnen dat schenden en dat kost
    anders een verspilde compile (undefined identifier)."""
    for m in _LOCAL_NAME_RE.finditer(txt):
        name = m.group(1)
        first = re.search(rf"\b{name}\b", txt)
        if first and first.start() < m.start(1):
            return False
    return True


def score(txt, func, mode, target, tmpdir, want_code=False):
    if not scope_ok(txt):
        return (10**9, None, None) if want_code else 10**9
    src = tmpdir / "cand.c"; obj = tmpdir / "cand.o"
    src.write_text(txt)
    obj.unlink(missing_ok=True)
    if not O.compile_src(src, obj, mode):
        return (10**9, None, None) if want_code else 10**9
    try:
        code, relocs = O.extract_func(obj.read_bytes(), func)
    except Exception:
        return (10**9, None, None) if want_code else 10**9
    if code is None or len(code) != len(target):
        s = 10**8 + abs(len(code or b"") - len(target))
        return (s, code, relocs) if want_code else s
    s = O.compare(target, code, relocs, mode, 0, verbose=False)
    return (s, code, relocs) if want_code else s


# ---- fase 1: deterministische patroon-sweep (de "NDS-permuter") -------------
# In plaats van random gokken: pas elke bekende mwcc-truc op ELKE toepasbare
# plek toe, één variant per (truc, plek). Gegarandeerde dekking van het bekende
# trucboek; random search is daarna alleen nog het vangnet voor het onbekende.

def _all_sites(txt, kind):
    """alle toepassings-plekken voor een blok-truc."""
    blocks = _if_blocks(txt)
    if kind == "arm_swap":
        return [b for b in blocks if b[5] >= 0]
    if kind == "nest_next":
        out = []
        for a in blocks:
            end_a = a[6] if a[5] >= 0 else a[4]
            # eerstvolgende blok dat NA a eindigt (dus geen geneste if)
            nxt = [b for b in blocks if b[0] > end_a]
            if not nxt: continue
            b = min(nxt, key=lambda x: x[0])
            if txt[end_a + 1:b[0]].strip() == "":
                out.append((a, b))
        return out
    if kind == "tail_dup":
        return [b for b in blocks if b[5] >= 0]
    return []


def sweep_variants(txt):
    """genereer alle enkelvoudige truc-toepassingen, plek voor plek."""
    out = []
    # blok-trucs op elke plek
    for s, cp, ce, to, tc, eo, ec in _all_sites(txt, "arm_swap"):
        cond = txt[cp + 1:ce]; then_b = txt[to + 1:tc]; else_b = txt[eo + 1:ec]
        out.append(("arm_swap", txt[:s] + f"if (!({cond})) {{{else_b}}} else {{{then_b}}}" + txt[ec + 1:]))
    for a, b in _all_sites(txt, "nest_next"):
        end_b = b[6] if b[5] >= 0 else b[4]
        piece = txt[b[0]:end_b + 1]
        # variant 1: nest in then-blok van A; variant 2 (als A een else heeft): in else-blok
        out.append(("nest_then", txt[:a[4]] + piece + "\n" + txt[a[4]:b[0]] + txt[end_b + 1:]))
        if a[5] >= 0:
            out.append(("nest_else", txt[:a[6]] + piece + "\n" + txt[a[6]:b[0]] + txt[end_b + 1:]))
    # regel-trucs op elke plek
    L = lines_of(txt)
    for i in range(len(L) - 1):
        if DECL_RE.match(L[i]) and DECL_RE.match(L[i + 1]):
            M = L[:]; M[i], M[i + 1] = M[i + 1], M[i]
            out.append(("decl_swap", "\n".join(M)))
    for i, l in enumerate(L):
        # compound-assign flips: x = x | y  <->  x |= y
        m = re.match(r"^(\s*)([\w\->\.\[\]]+)\s*=\s*\2\s*([|&+^-])\s*([^;]+);", l)
        if m:
            M = L[:]; M[i] = f"{m.group(1)}{m.group(2)} {m.group(3)}= {m.group(4)};"
            out.append(("compound", "\n".join(M)))
        m = re.match(r"^(\s*)([\w\->\.\[\]]+)\s*([|&+^-])=\s*([^;]+);", l)
        if m:
            M = L[:]; M[i] = f"{m.group(1)}{m.group(2)} = {m.group(2)} {m.group(3)} {m.group(4)};"
            out.append(("uncompound", "\n".join(M)))
        # u16-cast toevoegen/verwijderen bij returns en assignments
        if "return " in l and "(u16)" not in l:
            u16 = "(u16)" if "u16" in txt else "(unsigned short)"
            M = L[:]; M[i] = re.sub(r"return\s+", f"return {u16}", l, count=1)
            out.append(("u16_ret", "\n".join(M)))
        if "(u16)" in l:
            M = L[:]; M[i] = l.replace("(u16)", "", 1)
            out.append(("drop_u16", "\n".join(M)))
        # trick-operatoren deterministisch per plek
        if LOCAL_DECL_RE.match(l) and "volatile" not in l:
            mm = LOCAL_DECL_RE.match(l)
            M = L[:]; M[i] = l[:mm.end(2)] + " volatile" + l[mm.end(2):]
            out.append(("volatile", "\n".join(M)))
        if re.match(r"^\s+int\s+[ijk]\w{0,3}\s*[;=]", l):
            M = L[:]; M[i] = re.sub(r"^(\s+)int\b", r"\1unsigned short", l, count=1)
            out.append(("u16_ctr", "\n".join(M)))
    # pragma-variant één keer
    P = m_pragma_size(random.Random(0), L)
    if P: out.append(("pragma_size", "\n".join(P)))
    # do_while per for-lus (eerste)
    D = m_do_while(random.Random(0), L)
    if D: out.append(("do_while", "\n".join(D)))
    return out


def main():
    global O
    ap = argparse.ArgumentParser()
    ap.add_argument("--func", required=True)
    ap.add_argument("--src", type=pathlib.Path)
    ap.add_argument("--iters", type=int, default=600)
    ap.add_argument("--seed", type=int, default=1)
    ap.add_argument("--module")
    ap.add_argument("--oracle", default="mkds", choices=["mkds", "sm64ds"],
                    help="byte-oracle backend (mkds=aimatch/wibo, sm64ds=match-keten shim)")
    ap.add_argument("--no-sweep", action="store_true", help="sla fase 1 over")
    args = ap.parse_args()

    if args.oracle == "sm64ds":
        import sm64ds_oracle as O_mod
    else:
        import aimatch as O_mod
    O = O_mod

    rng = random.Random(args.seed)
    sym = O.find_symbol(args.func, args.module)
    if not sym:
        sys.exit(f"symbool {args.func} niet gevonden")
    mod, mode, addr, size = sym
    target = O.target_bytes(mod, addr, size)
    src = args.src or (MKDS / "ai/scratch" / f"agent_{addr:08x}.c")
    base = src.read_text()

    tmp_root = MKDS / ".wibo_tmp"; tmp_root.mkdir(exist_ok=True)
    with tempfile.TemporaryDirectory(dir=tmp_root) as td:
        tdp = pathlib.Path(td)
        cur_s, cur_code, cur_rel = score(base, args.func, mode, target, tdp, want_code=True)
        cur = base
        best, best_s = cur, cur_s
        syms = diagnose(target, cur_code, cur_rel or set(), mode) if cur_code else collections.Counter()
        if syms:
            print(f"[{args.func}] diagnose: {dict(syms.most_common(4))}", flush=True)
        pool = weighted_pool(syms)
        print(f"[{args.func}] start {cur_s} mismatches (seed {args.seed}, oracle {args.oracle})", flush=True)

        # ---- fase 1: patroon-sweep -----------------------------------------
        if not args.no_sweep:
            variants = sweep_variants(base)
            print(f"[{args.func}] sweep: {len(variants)} patroon-varianten", flush=True)
            for name, cand in variants:
                s = score(cand, args.func, mode, target, tdp)
                if s < best_s:
                    best, best_s = cand, s
                    print(f"[{args.func}] sweep {name}: -> {s}", flush=True)
                if s == 0:
                    out = src.with_suffix(".permuted.c")
                    out.write_text(cand)
                    print(f"[{args.func}] SWEEP-MATCH via {name} -> {out.name}", flush=True)
                    sys.exit(0)
            cur, cur_s = best, best_s   # random fase start vanaf beste sweep-stand
        stag = 0
        for it in range(args.iters):
            L = lines_of(cur)
            for _ in range(rng.randrange(1, 4)):
                mut = rng.choice(pool)
                out = mut(rng, L)
                if out: L = out
            cand = "\n".join(L)
            if cand == cur: continue
            s = score(cand, args.func, mode, target, tdp)
            if s < cur_s:
                cur, cur_s = cand, s; stag = 0
                if s < best_s:
                    best, best_s = cand, s
                    # her-diagnose op de nieuwe beste kandidaat -> gewichten bijstellen
                    s2, code2, rel2 = score(best, args.func, mode, target, tdp, want_code=True)
                    if code2 is not None and len(code2) == len(target):
                        syms = diagnose(target, code2, rel2 or set(), mode)
                        pool = weighted_pool(syms)
                    print(f"[{args.func}] it{it}: -> {s}  diagnose={dict(syms.most_common(3))}", flush=True)
                if s == 0: break
            else:
                stag += 1
                if stag > 60:   # restart vanaf origineel met andere pad
                    cur, cur_s = base, score(base, args.func, mode, target, tdp)
                    stag = 0
        out = src.with_suffix(".permuted.c")
        out.write_text(best)
        print(f"[{args.func}] KLAAR best={best_s} -> {out.name}", flush=True)
        sys.exit(0 if best_s == 0 else 1)


if __name__ == "__main__":
    main()
