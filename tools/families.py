#!/usr/bin/env python3
"""families.py — cluster ongematchte MKDS-functies op instructie-skelet.

Eén agent die de eerste van een familie kraakt, kraakt ze (bijna) allemaal —
gemeten: TEQSub-familie = 8 matches uit 1 agent. Deze tool vindt zulke families
vooraf, zodat elke agent-opdracht maximale opbrengst heeft.

Skelet = mnemonics + operanden met immediates/adressen genormaliseerd.
  tools/families.py [--min 0x18] [--max 0x200] [--top 20]
"""
import argparse
import json
import pathlib
import re
import sys
from collections import defaultdict

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent.parent.parent / "st/.venv/lib/python3.14/site-packages"))
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB

MKDS = pathlib.Path(__file__).resolve().parent.parent
CONFIG = MKDS / "config/eur/arm9"
EXTRACT = MKDS / "extract/eur"
MD = {"arm": Cs(CS_ARCH_ARM, CS_MODE_ARM), "thumb": Cs(CS_ARCH_ARM, CS_MODE_THUMB)}
SYM_RE = re.compile(r"(\S+) kind:function\((arm|thumb)(?:,size=(0x\w+))?\) addr:(0x\w+)")


def skeleton(code, mode, addr):
    out = []
    for i in MD[mode].disasm(code, addr):
        ops = re.sub(r"#\-?0x[0-9a-fA-F]+|#\-?\d+", "#", i.op_str)  # immediates weg
        out.append(f"{i.mnemonic} {ops}")
    return "\n".join(out)


def matched_addrs():
    addrs = set()
    mj = MKDS / "ai/matched.jsonl"
    if mj.is_file():
        for line in mj.read_text().splitlines():
            if line.strip():
                a = json.loads(line).get("addr", "?")
                if a != "?":
                    addrs.add(int(a, 16))
    for hf in MKDS.glob("ai/sdk_import_hits*.json"):
        for r in json.loads(hf.read_text()):
            addrs.add(int(r["addr"], 16))
    return addrs


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--min", type=lambda x: int(x, 0), default=0x18)
    ap.add_argument("--max", type=lambda x: int(x, 0), default=0x200)
    ap.add_argument("--top", type=int, default=20)
    args = ap.parse_args()

    data = (EXTRACT / "arm9/arm9.bin").read_bytes()
    done = matched_addrs()
    fams = defaultdict(list)
    tot = 0
    for line in (CONFIG / "symbols.txt").read_text().splitlines():
        m = SYM_RE.match(line)
        if not m or not m.group(3):
            continue
        addr, size = int(m.group(4), 16), int(m.group(3), 16)
        if addr in done or not (args.min <= size <= args.max):
            continue
        off = addr - 0x2000000
        if not (0 <= off and off + size <= len(data)):
            continue
        sk = skeleton(data[off:off + size], m.group(2), addr)
        if sk.count("\n") < 4:
            continue  # te klein om betekenisvol te clusteren
        fams[sk].append((m.group(1), addr, size))
        tot += 1

    families = sorted((v for v in fams.values() if len(v) >= 3), key=len, reverse=True)
    dekking = sum(len(f) for f in families)
    print(f"{tot:,} ongematchte functies geanalyseerd ({hex(args.min)}-{hex(args.max)})")
    print(f"{len(families)} families (>=3 leden) — samen {dekking:,} functies "
          f"({100*dekking/max(tot,1):.0f}% van de band)\n")
    print(f"top {args.top} families:")
    for f in families[:args.top]:
        name, addr, size = f[0]
        print(f"  {len(f):3}x  {size:4}B  bv. {name} @ 0x{addr:08x}")
    out = [{"leden": len(f), "size": f[0][2],
            "functies": [{"naam": n, "addr": hex(a)} for n, a, s in f]}
           for f in families]
    (MKDS / "ai/families.json").write_text(json.dumps(out, indent=1))
    print(f"\nvolledige lijst -> ai/families.json")


if __name__ == "__main__":
    main()
