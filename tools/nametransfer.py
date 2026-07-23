#!/usr/bin/env python3
"""nametransfer.py — stap 3: benoemde st-functies (SDK/libs) binair vergelijken
met anonieme MKDS-functies en bij hoge gelijkenis de naam overzetten.

  tools/nametransfer.py           # rapport (dry)
  tools/nametransfer.py --apply   # hernoem in config (alleen >= 0.97 + uniek)
"""
import argparse
import difflib
import json
import pathlib
import re
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent.parent.parent / "st/.venv/lib/python3.14/site-packages"))
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB

MKDS = pathlib.Path(__file__).resolve().parent.parent
STP = MKDS.parent / "st"
MD = {"arm": Cs(CS_ARCH_ARM, CS_MODE_ARM), "thumb": Cs(CS_ARCH_ARM, CS_MODE_THUMB)}
SYM_RE = re.compile(r"(\S+) kind:function\((arm|thumb)(?:,size=(0x\w+))?\) addr:(0x\w+)")


def mnems(code, mode, addr):
    return tuple(i.mnemonic for i in MD[mode].disasm(code, addr))


def st_named_corpus():
    """Alle st-functies met een echte C-naam (SDK-stijl: geen _Z-mangling, geen func_)."""
    data = (STP / "extract/eur/arm9/arm9.bin").read_bytes()
    out = []
    for line in (STP / "config/eur/arm9/symbols.txt").read_text().splitlines():
        m = SYM_RE.match(line)
        if not m or not m.group(3):
            continue
        name = m.group(1)
        if name.startswith(("func_", "_Z", "data_", "unknown")) or "_from_thumb" in name:
            continue
        addr, size = int(m.group(4), 16), int(m.group(3), 16)
        if size < 0x14 or size > 0x800:
            continue
        code = data[addr - 0x2000000:addr - 0x2000000 + size]
        mn = mnems(code, m.group(2), addr)
        if len(mn) >= 5:
            out.append((mn, frozenset(mn), name, size))
    return out


def mkds_unnamed():
    data = (MKDS / "extract/eur/arm9/arm9.bin").read_bytes()
    out = []
    for line in (MKDS / "config/eur/arm9/symbols.txt").read_text().splitlines():
        m = SYM_RE.match(line)
        if not m or not m.group(3):
            continue
        if not m.group(1).startswith("func_"):
            continue
        addr, size = int(m.group(4), 16), int(m.group(3), 16)
        if size < 0x14 or size > 0x800:
            continue
        code = data[addr - 0x2000000:addr - 0x2000000 + size]
        mn = mnems(code, m.group(2), addr)
        if len(mn) >= 5:
            out.append((mn, frozenset(mn), m.group(1), addr, size))
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--apply", action="store_true")
    ap.add_argument("--threshold", type=float, default=0.97)
    args = ap.parse_args()

    corpus = st_named_corpus()
    cands = mkds_unnamed()
    print(f"st benoemde corpus: {len(corpus)} | MKDS anoniem: {len(cands)}\n")

    transfers = []
    for mn, ops, fname, addr, size in cands:
        best, second = (0.0, None), 0.0
        for cmn, cops, cname, csize in corpus:
            if not (0.8 <= len(cmn) / max(len(mn), 1) <= 1.25):
                continue
            jac = len(ops & cops) / max(len(ops | cops), 1)
            if jac < 0.7:
                continue
            r = difflib.SequenceMatcher(None, mn, cmn).ratio()
            if r > best[0]:
                second = best[0]
                best = (r, cname)
            elif r > second:
                second = r
        if best[0] >= args.threshold and best[0] - second >= 0.02:
            transfers.append({"mkds": fname, "addr": hex(addr), "size": size,
                              "naam": best[1], "score": round(best[0], 3)})

    transfers.sort(key=lambda t: -t["score"])
    print(f"{len(transfers)} naam-transfers >= {args.threshold:.0%} (uniek beste):")
    for t in transfers[:30]:
        print(f"  {t['score']:.1%}  {t['mkds']} -> {t['naam']}  ({t['size']} B)")
    (MKDS / "ai/nametransfers.json").write_text(json.dumps(transfers, indent=1))

    if args.apply and transfers:
        symf = MKDS / "config/eur/arm9/symbols.txt"
        txt = symf.read_text()
        used = set(re.findall(r"^(\S+) ", txt, re.M))
        n = 0
        for t in transfers:
            new = t["naam"]
            if new in used:
                new = f"{new}__mkds_{t['addr'][-5:]}"
            txt2 = txt.replace(f"{t['mkds']} kind", f"{new} kind", 1)
            if txt2 != txt:
                txt = txt2
                used.add(new)
                n += 1
        symf.write_text(txt)
        print(f"\n{n} namen toegepast in config/eur/arm9/symbols.txt")


if __name__ == "__main__":
    main()
