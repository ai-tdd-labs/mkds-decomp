#!/usr/bin/env python3
"""aicoddog.py - rank unmatched functions by asm-similarity to matched ones.

Corpus = functions inside TUs marked `complete` in delinks.txt (their compiled
code is what links into the byte-verified ROM, so they are ground truth).
For each unmatched function, find the closest sibling by mnemonic-sequence
similarity and rank the worklist best-first.

  tools/aicoddog.py [--min 0x18] [--max 0x100] [--limit 25] [--module ovNNN]
"""

import argparse
import difflib
import pathlib
import re

from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB

ROOT = pathlib.Path(__file__).resolve().parent.parent
CONFIG = ROOT / "config" / "eur" / "arm9"
EXTRACT = ROOT / "extract" / "eur"

SYM_RE = re.compile(
    r"^(?P<name>\S+)\s+kind:function\((?P<mode>arm|thumb)(?:,size=(?P<size>0x[0-9a-fA-F]+))?\)"
    r"\s+addr:(?P<addr>0x[0-9a-fA-F]+)")

MD_ARM = Cs(CS_ARCH_ARM, CS_MODE_ARM)
MD_THUMB = Cs(CS_ARCH_ARM, CS_MODE_THUMB)


def modules():
    yield "arm9", CONFIG
    for ov in sorted((CONFIG / "overlays").iterdir()):
        if (ov / "symbols.txt").is_file():
            yield ov.name, ov


def parse_delinks(cfg):
    """Return (complete_ranges, claimed_ranges) lists of (start, end, file)."""
    complete, claimed = [], []
    blocks = {}
    cur = None
    for line in (cfg / "delinks.txt").read_text().splitlines():
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
    for f, b in blocks.items():
        for s, e in b["text"]:
            (complete if b["complete"] else claimed).append((s, e, f))
    return complete, claimed


def module_binary(module, cfg):
    if module == "arm9":
        return (EXTRACT / "arm9" / "arm9.bin").read_bytes(), 0x02000000
    data = (EXTRACT / "arm9_overlays" / f"{module}.bin").read_bytes()
    for line in (cfg / "delinks.txt").read_text().splitlines():
        m = re.search(r"start:(0x\w+)", line)
        if m:
            return data, int(m.group(1), 16)
    raise SystemExit(f"no base for {module}")


def mnemonics(code, mode, addr):
    md = MD_THUMB if mode == "thumb" else MD_ARM
    return tuple(i.mnemonic for i in md.disasm(code, addr))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--min", type=lambda x: int(x, 0), default=0x18)
    ap.add_argument("--max", type=lambda x: int(x, 0), default=0x100)
    ap.add_argument("--limit", type=int, default=25)
    ap.add_argument("--module")
    args = ap.parse_args()

    corpus = []      # (mnems, opset, name, file, module)
    candidates = []  # (mnems, opset, name, module, addr, size, mode)

    for mod, cfg in modules():
        complete, _ = parse_delinks(cfg)
        try:
            data, base = module_binary(mod, cfg)
        except (FileNotFoundError, SystemExit):
            continue
        claimed_all = [(s, e) for s, e, _ in complete]
        _, wip = parse_delinks(cfg)
        wip_ranges = [(s, e) for s, e, _ in wip]
        for line in (cfg / "symbols.txt").read_text().splitlines():
            m = SYM_RE.match(line)
            if not m:
                continue
            name, mode = m.group("name"), m.group("mode")
            addr = int(m.group("addr"), 16)
            size = int(m.group("size"), 16) if m.group("size") else 0
            if size < 0x8:
                continue
            code = data[addr - base: addr - base + size]
            hit = next((f for s, e, f in complete if s <= addr < e), None)
            if hit:
                mn = mnemonics(code, mode, addr)
                if mn:
                    corpus.append((mn, frozenset(mn), name, hit, mod))
            else:
                in_wip = any(s <= addr < e for s, e in wip_ranges)
                if in_wip:
                    continue  # iemand is er al mee bezig in een half-af TU
                if args.min <= size <= args.max and (not args.module or mod == args.module):
                    mn = mnemonics(code, mode, addr)
                    if mn:
                        candidates.append((mn, frozenset(mn), name, mod, addr, size, mode))

    print(f"corpus: {len(corpus)} matched functions (complete TUs), "
          f"candidates: {len(candidates)} unmatched in band\n")

    ranked = []
    for mn, ops, name, mod, addr, size, mode in candidates:
        best = (0.0, None, None)
        for cmn, cops, cname, cfile, cmod in corpus:
            if not (0.5 <= len(cmn) / max(len(mn), 1) <= 2.0):
                continue
            jac = len(ops & cops) / max(len(ops | cops), 1)
            if jac < 0.5 or jac < best[0] - 0.25:
                continue
            r = difflib.SequenceMatcher(None, mn, cmn).ratio()
            if r > best[0]:
                best = (r, cname, cfile)
        ranked.append((best[0], name, mod, addr, size, mode, best[1], best[2]))

    ranked.sort(reverse=True)
    for r, name, mod, addr, size, mode, sib, sibfile in ranked[:args.limit]:
        print(f"{r:5.0%}  {mod:5} {mode:5} 0x{addr:08x} sz=0x{size:<4x} {name}")
        if sib:
            print(f"       ~ {sib}  ({sibfile})")


if __name__ == "__main__":
    main()
