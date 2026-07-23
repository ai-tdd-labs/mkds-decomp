#!/usr/bin/env python3
"""clone.py — gratis post-pass (sm64ds-stijl clone + paramclone).

Voor elke ongematchte MKDS-functie: zoek een reeds byte-geverifieerde functie
(uit ai/matched.jsonl) waarvan de bytes identiek zijn op alle niet-reloc/niet-immediate
posities. clone = exact identiek (op relocaties na). paramclone = zelfde
instructie-skelet, alleen immediates/constanten verschillen -> herbruik de bron met
gesubstitueerde constanten. Nul tokens.

  tools/clone.py            # rapport (dry)
  tools/clone.py --apply    # schrijf gevonden bronnen naar ai/scratch/clone_*.c
"""
import argparse
import json
import pathlib
import re
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent.parent.parent / "st/.venv/lib/python3.14/site-packages"))
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB

MKDS = pathlib.Path(__file__).resolve().parent.parent
CONFIG = MKDS / "config/eur/arm9"
EXTRACT = MKDS / "extract/eur"
MD = {"arm": Cs(CS_ARCH_ARM, CS_MODE_ARM), "thumb": Cs(CS_ARCH_ARM, CS_MODE_THUMB)}
SYM_RE = re.compile(r"(\S+) kind:function\((arm|thumb)(?:,size=(0x\w+))?\) addr:(0x\w+)")


def arm9():
    return (EXTRACT / "arm9/arm9.bin").read_bytes()


def all_funcs():
    data = arm9()
    out = {}
    for line in (CONFIG / "symbols.txt").read_text().splitlines():
        m = SYM_RE.match(line)
        if not m or not m.group(3):
            continue
        addr, size = int(m.group(4), 16), int(m.group(3), 16)
        off = addr - 0x2000000
        if 0 <= off and off + size <= len(data) and size >= 0x20:
            out[addr] = (m.group(1), m.group(2), size, data[off:off + size])
    return out


def matched_addrs():
    """Adressen die al byte-geverifieerd zijn (ai/matched.jsonl of *_hits.json)."""
    addrs = {}
    mj = MKDS / "ai/matched.jsonl"
    if mj.is_file():
        for line in mj.read_text().splitlines():
            if line.strip():
                r = json.loads(line)
                a=r.get("addr","?");
                if a!="?": addrs[int(a,16)] = r.get("naam") or r.get("func")
    for hf in MKDS.glob("ai/sdk_import_hits*.json"):
        for r in json.loads(hf.read_text()):
            addrs.setdefault(int(r["addr"], 16), r.get("src") or r.get("mkds"))
    return addrs


def instr_skeleton(code, mode, addr):
    """Lijst (mnemonic, genormaliseerd-op-immediate) — immediates -> '#'."""
    out = []
    for i in MD[mode].disasm(code, addr):
        ops = re.sub(r"#\-?0x[0-9a-fA-F]+|#\-?\d+", "#", i.op_str)
        out.append((i.mnemonic, ops))
    return tuple(out)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--apply", action="store_true")
    args = ap.parse_args()

    funcs = all_funcs()
    done = matched_addrs()
    matched = [(a, funcs[a]) for a in done if a in funcs]
    unmatched = [(a, v) for a, v in funcs.items()
                 if a not in done and v[0].startswith("func_")]
    print(f"gematcht: {len(matched)} | ongematcht (func_): {len(unmatched)}\n")

    # skeleton-index van gematchte functies
    by_skel = {}
    by_bytes = {}
    for a, (name, mode, size, code) in matched:
        by_bytes.setdefault((size, code), (name, a))
        by_skel.setdefault(instr_skeleton(code, mode, a), []).append((name, a, code))

    clones, paramclones = [], []
    for a, (fname, mode, size, code) in unmatched:
        hit = by_bytes.get((size, code))
        if hit:
            clones.append((fname, a, hit[0], hit[1]))
            continue
        skel = instr_skeleton(code, mode, a)
        for sname, saddr, scode in by_skel.get(skel, []):
            if len(scode) == len(code):
                paramclones.append((fname, a, sname, saddr))
                break

    print(f"CLONES (exact byte-identiek aan gematchte functie): {len(clones)}")
    for f, a, s, sa in clones[:20]:
        print(f"  {f} @ 0x{a:08x}  ==  {s} @ 0x{sa:08x}")
    print(f"\nPARAMCLONES (zelfde skelet, andere constanten): {len(paramclones)}")
    for f, a, s, sa in paramclones[:20]:
        print(f"  {f} @ 0x{a:08x}  ~=  {s} @ 0x{sa:08x}")

    if args.apply:
        out = {"clones": [{"func": f, "addr": hex(a), "twin": s, "twin_addr": hex(sa)}
                          for f, a, s, sa in clones],
               "paramclones": [{"func": f, "addr": hex(a), "twin": s, "twin_addr": hex(sa)}
                               for f, a, s, sa in paramclones]}
        (MKDS / "ai/clones.json").write_text(json.dumps(out, indent=1))
        print(f"\nopgeslagen in ai/clones.json ({len(clones)} clones, {len(paramclones)} paramclones)")


if __name__ == "__main__":
    main()
