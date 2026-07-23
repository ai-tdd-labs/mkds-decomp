#!/usr/bin/env python3
"""wave_prep.py — kies de beste doelen voor een agent-golf en schrijf briefings.

Doelselectie (context-rijk = hoge slaagkans, zoals golf 3 bewees):
  - ongematchte arm-functies 0x40..0x300 in arm9,
  - gerangschikt op contextscore: aandeel callees dat al BENOEMD of GEMATCHT is,
    plus bonus als de functie zelf een string raakt (naambaar) of in een regio
    vol matches ligt.
Per doel komt een briefing in ai/wave/brief_<addr>.md met: config-naam/size/mode,
volledige disassembly met callee-namen, gedecodeerde pool-woorden (symbool of
string), en de standaard werkwijze-instructies voor de agent.

  tools/wave_prep.py [--count 6] [--min 0x40] [--max 0x300]
"""
import argparse
import datetime
import json
import os
import pathlib
import re
import struct
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent.parent.parent / "st/.venv/lib/python3.14/site-packages"))
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB  # noqa: E402

MKDS = pathlib.Path(__file__).resolve().parent.parent
CONFIG = MKDS / "config/eur/arm9"
EXTRACT = MKDS / "extract/eur"
WAVE = MKDS / "ai/wave"
MD = {"arm": Cs(CS_ARCH_ARM, CS_MODE_ARM), "thumb": Cs(CS_ARCH_ARM, CS_MODE_THUMB)}
SYM = re.compile(r"(\S+) kind:function\((arm|thumb)(?:,size=(0x\w+))?\) addr:(0x\w+)")


def load_all():
    o = (EXTRACT / "arm9/arm9.bin").read_bytes()
    names, funcs = {}, {}
    for line in (CONFIG / "symbols.txt").read_text().splitlines():
        m = re.match(r"(\S+) kind:\S+ addr:(0x\w+)", line)
        if m:
            names[int(m.group(2), 16)] = m.group(1)
        f = SYM.match(line)
        if f and f.group(3):
            funcs[int(f.group(4), 16)] = (f.group(1), f.group(2), int(f.group(3), 16))
    done = set()
    for line in (MKDS / "ai/matched.jsonl").read_text().splitlines():
        if line.strip():
            a = json.loads(line).get("addr", "?")
            if a != "?":
                done.add(int(a, 16))
    for hf in MKDS.glob("ai/sdk_import_hits*.json"):
        for r in json.loads(hf.read_text()):
            done.add(int(r["addr"], 16))
    quar = set()
    qf = MKDS / "ai/hangin_quarantine.txt"
    if qf.is_file():
        quar = {int(x, 16) for x in qf.read_text().split() if x.strip()}
    return o, names, funcs, done, quar


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


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--count", type=int, default=6)
    ap.add_argument("--min", type=lambda x: int(x, 0), default=0x40)
    ap.add_argument("--max", type=lambda x: int(x, 0), default=0x300)
    ap.add_argument("--funcs", help="komma-lijst met exacte doelnamen (overslaat scoring)")
    args = ap.parse_args()

    o, names, funcs, done, quar = load_all()
    base = 0x02000000
    # kennisbank: trucs + bekende structs (agents lezen hieruit én schrijven erin)
    tricks = []
    tf = MKDS / "ai/tricks.jsonl"
    if tf.is_file():
        tricks = [json.loads(l) for l in tf.read_text().splitlines() if l.strip()]
    structs = {}
    sf = MKDS / "ai/structs.jsonl"
    if sf.is_file():
        for l in sf.read_text().splitlines():
            if l.strip():
                r = json.loads(l)
                g = str(r.get("global", "")).split("@")[0].strip()
                try:
                    structs[int(g, 16)] = r
                except (ValueError, TypeError):
                    continue  # niet-hex sleutel (agent-notitie) — sla over
    facts = {}
    ff = MKDS / "ai/funcfacts.jsonl"
    if ff.is_file():
        for l in ff.read_text().splitlines():
            if l.strip():
                r = json.loads(l)
                facts[r["func"]] = r

    # claims: voorkom dat twee AI-sessies (Claude-golf, Codex, Terra, ...) dezelfde
    # functie kraken — sm64ds-idee, als simpel repo-bestand (workers delen deze git)
    claims = {}
    cf = MKDS / "ai/claims.jsonl"
    if cf.is_file():
        for l in cf.read_text().splitlines():
            if l.strip():
                r = json.loads(l)
                claims[r["func"]] = r  # laatste regel per func wint (append-log)
    who = os.environ.get("WAVE_WHO", "claude-main")

    # sweep-skiplijst: uitgestelde missers (ai/wave/skip.txt, één adres per regel)
    # zodat de sweep ze niet elke batch opnieuw kiest; herkansing pakt ze later.
    skip = set()
    skf = MKDS / "ai/wave/skip.txt"
    if skf.is_file():
        for l in skf.read_text().split():
            try:
                skip.add(int(l, 16))
            except ValueError:
                pass

    cands = []
    for addr, (nm, mode, sz) in funcs.items():
        if addr in done or addr in quar or addr in skip or not (args.min <= sz <= args.max):
            continue
        c = claims.get(nm)
        if c and c.get("status") == "active" and c.get("who") != who:
            continue  # geclaimd door een andere worker
        code = o[addr - base:addr - base + sz]
        ins = list(MD[mode].disasm(code, addr))
        if len(ins) < 4:
            continue
        calls = []
        for i in ins:
            if i.mnemonic in ("bl", "blx") and i.op_str.startswith("#"):
                t = int(i.op_str[1:], 16) & ~1
                cn = names.get(t) or names.get(t | 1) or f"0x{t:08x}"
                calls.append((i.address, i.mnemonic, t, cn))
        if not calls:
            continue  # leaf-functies laat coddog/families doen; agents op call-rijke
        known = sum(1 for _, _, t, cn in calls
                    if not cn.startswith("0x") and (not cn.startswith("func_") or t in done))
        score = known / len(calls)
        has_str = any(string_at(o, struct.unpack_from("<I", code, off)[0])
                      for off in range(0, len(code) - 3, 4))
        score += 0.3 if has_str else 0
        # blx r<reg> (indirecte calls) maken het moeilijker; kleine straf
        if any(i.mnemonic == "blx" and not i.op_str.startswith("#") for i in ins):
            score -= 0.2
        cands.append((score, addr, nm, mode, sz, ins, calls))

    cands.sort(key=lambda x: (-x[0], x[4]))
    # coddog-corpus één keer opbouwen (fuzzy voorbeeld-ophaler)
    try:
        import coddog
        _cd_syms = coddog._sym_table()
        _cd_corpus = coddog.build_corpus(_cd_syms, coddog._matched_names())
    except Exception as e:
        print(f"  (coddog uit: {e})")
        coddog = None; _cd_syms = {}; _cd_corpus = []
    WAVE.mkdir(parents=True, exist_ok=True)
    # MERGE, don't wipe: with --funcs only the targeted briefs are (re)written;
    # briefs of other in-flight agents stay untouched. A full auto-pick run
    # (no --funcs) still starts clean, since those briefs are its own output.
    if not args.funcs:
        for old in WAVE.glob("brief_*.md"):
            old.unlink()

    if args.funcs:
        want = {f.strip() for f in args.funcs.split(",")}
        picked = [c for c in cands if c[2] in want]
        missing = want - {c[2] for c in picked}
        if missing:
            print(f"!! niet gevonden als kandidaat: {sorted(missing)}")
    else:
        picked = cands[:args.count]
    manifest = []
    for score, addr, nm, mode, sz, ins, calls in picked:
        lines = [f"# Doel: {nm} @ 0x{addr:08x}  size=0x{sz:x}  mode={mode}  (contextscore {score:.2f})",
                 "", "## Disassembly (ROM, met callee-namen):", "```"]
        for i in ins:
            t = ""
            if i.mnemonic in ("bl", "blx") and i.op_str.startswith("#"):
                tg = int(i.op_str[1:], 16) & ~1
                t = f"   ; {names.get(tg) or names.get(tg | 1) or '?'}"
            lines.append(f"{i.address:08x}  {i.mnemonic:8}{i.op_str}{t}")
        lines += ["```", "", "## Pool-woorden (gedecodeerd):"]
        code = o[addr - base:addr - base + sz]
        for off in range(0, len(code) - 3, 4):
            w = struct.unpack_from("<I", code, off)[0]
            if 0x01ff0000 <= w < 0x02800000 or w >= 0x04000000 and w < 0x05000000:
                s = string_at(o, w)
                lbl = f'string "{s}"' if s else (names.get(w) or names.get(w & ~1) or "geen symbool")
                lines.append(f"- func+0x{off:x}: 0x{w:08x} -> {lbl}")
        # bekende structs bij de pool-globals van dit doel
        known = []
        for off in range(0, len(code) - 3, 4):
            w = struct.unpack_from("<I", code, off)[0]
            if w in structs:
                s = structs[w]
                known.append(f"- {s['naam']} @ {s['global']} (size {s['size']}): {s['def']}  [bron: {s['bron']}]")
        if known:
            lines += ["", "## Bekende structs op globals die deze functie raakt (NIET opnieuw afleiden):"] + known
        # feiten over de callees die we al gematcht hebben: signatuur + samenvatting
        cf = []
        for _, _, _, cn in calls:
            r = facts.get(cn)
            if r and r["func"] not in {x.split(" ", 1)[0] for x in cf}:
                cf.append(f"- {r['sig']}" + (f"  — {r['doc']}" if r['doc'] else ""))
        if cf:
            lines += ["", "## Bekende signaturen van callees (al gematcht — gebruik deze exact):"] + cf
        lines += ["", "## Codegen-trucs uit eerdere matches (ai/tricks.jsonl):"]
        lines += [f"- {r.get('truc', r.get('rule',''))} — {r.get('wanneer', r.get('when',''))}"
                  for r in tricks if r.get('truc') or r.get('rule')]
        # coddog: 2-3 fuzzy-gelijkende AL-GEMATCHTE functies als few-shot-voorbeeld
        try:
            sibs = coddog.rank(nm, _cd_syms, _cd_corpus, top=3) if coddog else []
        except Exception:
            sibs = []
        if sibs:
            lines += ["", "## Meest gelijkende al-gematchte functies (few-shot — "
                      "leun hierop, dit is vaak vrijwel dezelfde vorm):"]
            for score, sib_name, sib_src in sibs:
                lines += [f"### {sib_name}  ({score:.0%} opcode-overlap) — {sib_src.relative_to(MKDS)}",
                          "```c", sib_src.read_text().strip(), "```"]
        lines += ["", "## Werkwijze",
                  f"1. Schrijf ai/scratch/agent_{addr:08x}.c met functie `{nm}`.",
                  "   START the file with a comment block. Its FIRST line MUST be:",
                  "   'PURPOSE: <one short, simple sentence in plain English saying what this",
                  "   function is FOR>' — so simple that a modder without compiler knowledge",
                  "   instantly gets it (e.g. 'PURPOSE: Plays the crash sound when a kart hits",
                  "   a wall.'). Then 2-5 lines detail (ENGLISH): arguments, behaviour. Mark",
                  "   uncertainty explicitly ('probably...'). Add short inline comments on",
                  "   tricky lines. Comments never affect bytes — free docs.",
                  "   Gebruik EXACT de config-namen hierboven voor externe functies/data.",
                  "   Vast adres buiten arm9 (0x027..., 0x04...): directe volatile-pointer, GEEN extern.",
                  "   Strings NOOIT als literal (\"x.nsbmd\") — dat maakt een NIEUWE lokale string",
                  "   die de link breekt; gebruik het data_<adres>-symbool uit de pool-lijst hierboven.",
                  f"2. Verifieer: ../st/.venv/bin/python tools/aimatch.py --src ai/scratch/agent_{addr:08x}.c "
                  f"--func {nm} --module arm9 --addr 0x{addr:08x} --size 0x{sz:x} --quiet  (zoek match=True)",
                  "3. Bij mismatch: compileer los (mwccarm -O4,p -enum int -lang c99 -char signed "
                  "-interworking -proc arm946e -gccext,on -msgstyle gcc), disassemble met capstone, "
                  "vergelijk instructie-voor-instructie, itereer. Raadpleeg de trucs-lijst hierboven.",
                  "3b. KENNIS TERUGSCHRIJVEN (verplicht): ontdekte je een NIEUWE truc die beslissend",
                  "   was (niet in de lijst hierboven)? Append 1 JSON-regel aan ai/tricks.jsonl:",
                  "   {\"truc\": \"...\", \"wanneer\": \"...\", \"bron\": \"<functienaam>\"}.",
                  "   Leidde je een STRUCT af op een globale? Append aan ai/structs.jsonl:",
                  "   {\"global\": \"0x...\", \"naam\": \"...\", \"size\": \"0x...\", \"def\": \"offset:type veld; ...\", \"bron\": \"<functienaam>\"}.",
                  "   Dit zijn de ENIGE twee bestanden buiten je eigen scratch die je mag aanraken.",
                  "4. STOP bij match=True. Rapporteer pad + exacte inhoud. Draai NIET build.sh."]
        bf = WAVE / f"brief_{addr:08x}.md"
        bf.write_text("\n".join(lines) + "\n")
        manifest.append({"addr": hex(addr), "func": nm, "size": hex(sz), "brief": str(bf.relative_to(MKDS)),
                         "score": round(score, 2)})
    (WAVE / "manifest.json").write_text(json.dumps(manifest, indent=1))
    # claim de gekozen doelen (append-log; laatste regel per func wint)
    with (MKDS / "ai/claims.jsonl").open("a") as f:
        for m in manifest:
            f.write(json.dumps({"func": m["func"], "addr": m["addr"], "who": who,
                                "date": datetime.date.today().isoformat(),
                                "status": "active"}) + "\n")
    print(f"{len(picked)} briefings -> ai/wave/ (van {len(cands)} kandidaten)")
    for m in manifest:
        print(f"  {m['func']} @{m['addr']} size={m['size']} score={m['score']}")


if __name__ == "__main__":
    main()
