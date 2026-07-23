#!/usr/bin/env python3
"""crossgame.py — cross-game similarity: rank MKDS-functies tegen het
st-corpus (gematchte functies mét bron) op mnemonic-gelijkenis.

  tools/crossgame.py [--min 0x20] [--max 0x200] [--limit 30]
"""
import argparse
import difflib
import pathlib
import re
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent.parent.parent / "st/.venv/lib/python3.14/site-packages"))
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB

MKDS = pathlib.Path(__file__).resolve().parent.parent
STP = MKDS.parent / "st"
MD_ARM = Cs(CS_ARCH_ARM, CS_MODE_ARM)
MD_TH = Cs(CS_ARCH_ARM, CS_MODE_THUMB)

SYM_RE = re.compile(r"(\S+) kind:function\((arm|thumb)(?:,size=(0x\w+))?\) addr:(0x\w+)")


def mnems(code, mode, addr):
    md = MD_TH if mode == "thumb" else MD_ARM
    return tuple(i.mnemonic for i in md.disasm(code, addr))


def st_corpus():
    """Functies in complete-TU's van st: (mnems, opset, naam, bronbestand)."""
    cfg = STP / "config/eur/arm9"
    out = []

    def harvest(cfgdir, binpath, base):
        if not binpath.is_file() or not (cfgdir / "delinks.txt").is_file():
            return
        blocks, cur = {}, None
        for line in (cfgdir / "delinks.txt").read_text().splitlines():
            if line and not line[0].isspace() and line.rstrip().endswith(":"):
                cur = line.strip()[:-1]
                blocks[cur] = {"complete": False, "text": []}
            elif cur:
                if line.strip() == "complete":
                    blocks[cur]["complete"] = True
                elif ".text" in line:
                    m = re.search(r"start:(0x\w+)\s+end:(0x\w+)", line)
                    if m:
                        blocks[cur]["text"].append((int(m.group(1), 16), int(m.group(2), 16)))
        comp = [(s, e, f) for f, b in blocks.items() if b["complete"] for s, e in b["text"]]
        if not comp:
            return
        data = binpath.read_bytes()
        for line in (cfgdir / "symbols.txt").read_text().splitlines():
            m = SYM_RE.match(line)
            if not m or not m.group(3):
                continue
            addr, size = int(m.group(4), 16), int(m.group(3), 16)
            src = next((f for s, e, f in comp if s <= addr < e), None)
            if src and size >= 0x18:
                code = data[addr - base:addr - base + size]
                mn = mnems(code, m.group(2), addr)
                if mn:
                    out.append((mn, frozenset(mn), m.group(1), src))

    harvest(cfg, STP / "extract/eur/arm9/arm9.bin", 0x02000000)
    for ov in sorted((cfg / "overlays").glob("*")):
        d = ov / "delinks.txt"
        if d.is_file():
            base = next((int(m.group(1), 16) for line in d.read_text().splitlines()
                         if (m := re.search(r"start:(0x\w+)", line))), None)
            if base:
                harvest(ov, STP / f"extract/eur/arm9_overlays/{ov.name}.bin", base)
    return out


def mkds_candidates(minsz, maxsz):
    cfg = MKDS / "config/eur/arm9"
    data = (MKDS / "extract/eur/arm9/arm9.bin").read_bytes()
    out = []
    for line in (cfg / "symbols.txt").read_text().splitlines():
        m = SYM_RE.match(line)
        if not m or not m.group(3):
            continue
        addr, size = int(m.group(4), 16), int(m.group(3), 16)
        if not (minsz <= size <= maxsz):
            continue
        code = data[addr - 0x2000000:addr - 0x2000000 + size]
        mn = mnems(code, m.group(2), addr)
        if mn:
            out.append((mn, frozenset(mn), m.group(1), addr, size, m.group(2)))
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--min", type=lambda x: int(x, 0), default=0x20)
    ap.add_argument("--max", type=lambda x: int(x, 0), default=0x200)
    ap.add_argument("--limit", type=int, default=30)
    args = ap.parse_args()

    corpus = st_corpus()
    cands = mkds_candidates(args.min, args.max)
    print(f"st-corpus: {len(corpus)} gematchte functies | MKDS-kandidaten: {len(cands)}\n")

    ranked = []
    for mn, ops, name, addr, size, mode in cands:
        best = (0.0, None, None)
        for cmn, cops, cname, csrc in corpus:
            if not (0.55 <= len(cmn) / max(len(mn), 1) <= 1.8):
                continue
            jac = len(ops & cops) / max(len(ops | cops), 1)
            if jac < 0.55 or jac < best[0] - 0.2:
                continue
            r = difflib.SequenceMatcher(None, mn, cmn).ratio()
            if r > best[0]:
                best = (r, cname, csrc)
        if best[0] > 0.6:
            ranked.append((best[0], name, addr, size, mode, best[1], best[2]))

    ranked.sort(reverse=True)
    print(f"{len(ranked)} kandidaten boven 60% gelijkenis; top {args.limit}:\n")
    for r, name, addr, size, mode, sib, src in ranked[:args.limit]:
        print(f"{r:5.0%}  {mode:5} 0x{addr:08x} sz=0x{size:<4x} {name}")
        print(f"       ~ st:{sib}  ({src})")


if __name__ == "__main__":
    main()
