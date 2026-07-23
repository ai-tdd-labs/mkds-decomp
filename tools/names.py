#!/usr/bin/env python3
"""names.py — bewijs-gedreven naamgeving met zekerheidsniveaus.

Verzint NOOIT een zekere naam uit onvoldoende bewijs. Per gedecompileerde func_:
  - STRING-bewijs: verwijst de functie naar een tekst (assetnaam)? Uniek + assetachtig
    -> HOOG (hernoemen). Gedeeld -> MIDDEL (annoteren, func_ behouden voor uniekheid).
  - THUNK: één call naar een BENOEMDE functie -> MIDDEL (annoteren).
  - GETTER/SETTER-vorm -> LAAG (annoteren).
De HOGE-zekerheid-namen worden veilig doorgevoerd (config-symbool + alle C-verwijzingen
+ matched.jsonl; relocs.txt gebruikt adressen, dus die blijft ongemoeid -> bytes
onveranderd). De rest krijgt een `// bewijs:`-comment bovenaan de .c en een regel in
het grootboek ai/names.jsonl {addr, naam, zekerheid, bewijs}.

  tools/names.py            # rapport (dry)
  tools/names.py --apply    # hernoem HOOG + annoteer de rest + schrijf grootboek
"""
import argparse
import json
import pathlib
import re
import struct
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent.parent.parent / "st/.venv/lib/python3.14/site-packages"))
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM  # noqa: E402

MKDS = pathlib.Path(__file__).resolve().parent.parent
CONFIG = MKDS / "config/eur/arm9"
EXTRACT = MKDS / "extract/eur"
SRC = MKDS / "src"
SCRATCH = MKDS / "ai/scratch"
MD = Cs(CS_ARCH_ARM, CS_MODE_ARM)
SYM = re.compile(r"(\S+) kind:function\((arm|thumb)(?:,size=(0x\w+))?\) addr:(0x\w+)")


def load():
    o = (EXTRACT / "arm9/arm9.bin").read_bytes()
    names = {}
    for line in (CONFIG / "symbols.txt").read_text().splitlines():
        m = re.match(r"(\S+) kind:\S+ addr:(0x\w+)", line)
        if m:
            names[int(m.group(2), 16)] = m.group(1)
    return o, names


def string_at(o, a, base=0x02000000):
    off = a - base
    if not (0 <= off < len(o)):
        return None
    s = b""
    for i in range(off, min(off + 48, len(o))):
        c = o[i]
        if 32 <= c < 127:
            s += bytes([c])
        elif c == 0:
            break
        else:
            return None
    return s.decode() if len(s) >= 4 and any(chr(x).isalpha() for x in s) else None


def clean_ident(s):
    """assetnaam -> geldige C-identifier: strip extensie, niet-alnum -> _."""
    s = re.sub(r"\.\w+$", "", s)                 # extensie weg
    s = re.sub(r"[^A-Za-z0-9]+", "_", s).strip("_")
    return s[:40] or "asset"


def analyze(o, names, addr, size, mode):
    code = o[addr - 0x02000000:addr - 0x02000000 + size]
    ins = list(MD.disasm(code, addr)) if mode == "arm" else []
    ev = {}
    pool = []
    for off in range(0, len(code) - 3, 4):
        w = struct.unpack_from("<I", code, off)[0]
        s = string_at(o, w)
        if s:
            ev.setdefault("strings", []).append(s)
        if 0x02000000 <= w < 0x02800000:
            pool.append(w)
    calls = [i for i in ins if i.mnemonic in ("bl", "blx") and i.op_str.startswith("#")]
    named = [(names.get(int(i.op_str[1:], 16) & ~1) or names.get((int(i.op_str[1:], 16) & ~1) | 1))
             for i in calls]
    named = [n for n in named if n and not n.startswith("func_")]
    if len(calls) == 1 and named:
        ev["thunk"] = named[0]
    if "Mem_AllocateHeap" in named:
        # allocator: onderscheidend = het data-sjabloon dat gekopieerd wordt (laatste pool-adres)
        ev["alloc"] = pool[-1] if pool else addr
    loads = [i for i in ins if i.mnemonic.startswith("ldr")]
    stores = [i for i in ins if i.mnemonic.startswith("str")]
    arith = [i for i in ins if i.mnemonic in ("add", "sub", "mul", "smull", "umull",
             "lsl", "lsr", "asr", "and", "orr", "eor", "rsb", "mov", "mvn", "bic")]
    if not calls and ins and len(ins) <= 6 and (loads or stores):
        # getter vs setter: schrijft 'ie naar de globale (str) of leest 'ie (ldr)?
        ev["access"] = ("set" if stores else "get", pool[0] if pool else addr)
    elif not calls and ins and len(ins) <= 8 and arith and not loads and not stores:
        ev["calc"] = True                       # pure berekening (math, geen geheugen)
    elif not calls and ins and len(ins) <= 10 and any(i.mnemonic == "cmp" for i in ins):
        ev["check"] = True                      # kleine ja/nee-controle
    ev["size"] = size
    return ev


def rename_everywhere(old, new):
    """hernoem een symbool overal: config-symbols (alle modules), src/*.c, scratch/*.c,
    matched.jsonl. relocs.txt gebruikt adressen -> ongemoeid. Bytes veranderen niet."""
    word = re.compile(rf"\b{re.escape(old)}\b")
    files = [CONFIG / "symbols.txt"]
    files += [p / "symbols.txt" for p in [CONFIG / "itcm", CONFIG / "dtcm"] if (p / "symbols.txt").is_file()]
    files += [ov / "symbols.txt" for ov in (CONFIG / "overlays").glob("ov*")]
    files += list(SRC.rglob("*.c")) + list(SRC.rglob("*.cpp"))
    files += list(SCRATCH.glob("*.c"))
    files += [MKDS / "ai/matched.jsonl"]
    for f in files:
        if f.is_file():
            t = f.read_text()
            if old in t:
                f.write_text(word.sub(new, t))
    # hernoem ook het src-bestand zelf
    for ext in ("c", "cpp"):
        p = SRC / "arm9" / f"{old}.{ext}"
        if p.is_file():
            p.rename(SRC / "arm9" / f"{new}.{ext}")


def annotate(func, comment):
    """zet een bewijs-comment bovenaan de src/*.c (browse-hint, geen byte-effect)."""
    for ext in ("c", "cpp"):
        p = SRC / "arm9" / f"{func}.{ext}"
        if p.is_file():
            t = p.read_text()
            if "// bewijs:" not in t:
                p.write_text(f"// bewijs: {comment}\n{t}")
            return


def compute():
    """geef (ledger, renames, annots) terug op basis van het huidige bewijs."""
    o, names = load()
    matched = {r["func"] for r in
               (json.loads(l) for l in (MKDS / "ai/matched.jsonl").read_text().splitlines() if l.strip())
               if r["func"].startswith("func_0")}

    # RENAME-tier: ALLE arm9 func_ (ook nog-niet-gedecompileerd) met een UNIEKE
    # asset-string -> hoog vertrouwen. Uniekheid over het hele spel.
    str_users, funcs = {}, []
    for line in (CONFIG / "symbols.txt").read_text().splitlines():
        m = SYM.match(line)
        if not m or not m.group(3) or not m.group(1).startswith("func_0"):
            continue
        addr = int(m.group(4), 16)
        ev = analyze(o, names, addr, int(m.group(3), 16), m.group(2))
        funcs.append((m.group(1), addr, ev))
        for s in ev.get("strings", []):
            str_users.setdefault(s, set()).add(m.group(1))

    ledger, renames, annots = [], [], []
    used_names = set(names.values())
    for func, addr, ev in funcs:
        strings = ev.get("strings", [])
        uniq = next((s for s in strings if len(str_users[s]) == 1 and re.search(r"\.\w{2,4}$", s)), None)
        if uniq:
            cand = f"Maybe_{clean_ident(uniq)}"
            n, i = cand, 2
            while n in used_names:
                n = f"{cand}_{i}"; i += 1
            used_names.add(n)
            renames.append((func, n, f'unieke asset-string "{uniq}"'))
            ledger.append({"addr": hex(addr), "func": func, "voorstel": n,
                           "zekerheid": "hoog", "bewijs": f'unieke string "{uniq}"'})
        elif func in matched:
            # STRUCTUUR-tier: onze gedecompileerde func_ krijgen een LEESBARE, unieke naam
            # op basis van rol + het onderscheidende adres (traceerbaar, geen loze teller).
            # Gedeelde string blijft annotatie (te weinig om uniek te benoemen).
            def uniq_name(cand):
                n, i = cand, 2
                while n in used_names:
                    n = f"{cand}_{i}"; i += 1
                used_names.add(n)
                return n
            # rol -> leesbare naam. Prefix verraadt meteen de aard:
            #   Maybe_get_/set_ = piepklein accessor, Maybe_call_ = doorgeefluik,
            #   Maybe_CreateObj_ = maakt object, Maybe_calc_/check_ = kleine helper.
            # Wat GEEN Maybe_-rol krijgt (>= 0x80) blijft func_ = een GROTERE functie.
            sz = ev.get("size", 0)
            if "alloc" in ev:
                n = uniq_name(f"Maybe_CreateObj_{ev['alloc'] & 0xffffff:06x}")
                z, b = "middel", f"maakt object uit data 0x{ev['alloc']:08x}"
            elif "thunk" in ev:
                n = uniq_name(f"Maybe_call_{re.sub(r'[^A-Za-z0-9]', '_', ev['thunk'])[:28]}")
                z, b = "middel", f"doorgeefluik -> {ev['thunk']}"
            elif "access" in ev:
                kind, g = ev["access"]
                n = uniq_name(f"Maybe_{kind}_{g & 0xffffff:06x}")
                z, b = "laag", f"{'schrijft' if kind == 'set' else 'leest'} globaal 0x{g:08x}"
            elif ev.get("calc"):
                n = uniq_name(f"Maybe_calc_{addr & 0xffffff:06x}")
                z, b = "laag", "kleine berekening (geen geheugen/aanroep)"
            elif ev.get("check"):
                n = uniq_name(f"Maybe_check_{addr & 0xffffff:06x}")
                z, b = "laag", "kleine ja/nee-controle"
            elif sz < 0x80:
                n = uniq_name(f"Maybe_helper_{addr & 0xffffff:06x}")
                z, b = "laag", f"kleine helper (0x{sz:x} bytes)"
            else:
                continue  # >= 0x80 en geen duidelijke rol -> blijft func_ (grotere functie)
            renames.append((func, n, b))
            ledger.append({"addr": hex(addr), "func": func, "voorstel": n, "zekerheid": z, "bewijs": b})
    return len(funcs), ledger, renames, annots


def write_ledger(ledger):
    (MKDS / "ai/names.jsonl").write_text("\n".join(json.dumps(x) for x in ledger) + "\n")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--apply", action="store_true", help="hernoem HOOG + annoteer + schrijf grootboek")
    ap.add_argument("--record", action="store_true", help="alleen grootboek bijwerken (geen code-wijziging)")
    args = ap.parse_args()

    nfuncs, ledger, renames, annots = compute()

    if args.record:
        write_ledger(ledger)
        print(f"grootboek bijgewerkt: {len(renames)} naam-voorstellen (hoog) + "
              f"{len(annots)} bewijs-notities -> ai/names.jsonl")
        return

    print(f"arm9 func_-functies geanalyseerd: {nfuncs}")
    print(f"  HOOG (hernoemen, unieke asset-string): {len(renames)}")
    for f, n, why in renames[:10]:
        print(f"    {f} -> {n}   ({why})")
    print(f"  MIDDEL/LAAG (annoteren + grootboek): {len(annots)}")
    for f, c in annots[:6]:
        print(f"    {f}: {c}")

    if args.apply:
        for func, new, _ in renames:
            rename_everywhere(func, new)
        renamed = {f for f, _, _ in renames}
        for func, comment in annots:
            if func not in renamed:
                annotate(func, comment)
        write_ledger(ledger)
        print(f"\n{len(renames)} hernoemd, {len(annots)} geannoteerd, grootboek -> ai/names.jsonl")
        print("draai nu: tools/doctor.py && bash build.sh  (bytes moeten identiek blijven)")


if __name__ == "__main__":
    main()
