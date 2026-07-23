#!/usr/bin/env python3
"""nearmiss_route.py — vliegwiel-router voor de near-miss-database.

Leest ai/wave/nearmiss/*.txt (oracle-uitvoer per misser), haalt de mismatch-
telling eruit en routeert:
  - mismatches <= drempel (default 8): draai de deterministische permuter-sweep
    (permute2 fase 1 = alle bekende mwcc-trucs, GEEN model/quota nodig)
  - anders: laat staan voor de volgende trechter-laag (model-pen)
Geslaagde sweeps schrijven de gefixte C terug naar ai/scratch/agent_<addr>.c
zodat register_batch (mét WRONG-DEST-poort) ze oppakt.

  tools/nearmiss_route.py [--max-mm 8] [--iters 40] [--limit 50] [--dry]
Heraanval-flow bij een nieuw bewezen truc: gewoon opnieuw draaien — de sweep
kent de nieuwe truc dan al (permute2 leest tricks-patronen bij de start).
"""
import argparse
import json
import pathlib
import re
import subprocess

MKDS = pathlib.Path(__file__).resolve().parent.parent
PY = str(MKDS.parent / "st/.venv/bin/python")
NM = MKDS / "ai/wave/nearmiss"
MM_RE = re.compile(r"mismatches=(\d+)/(\d+)")


def sym_info(addr):
    pat = re.compile(rf"(\S+) kind:function\((arm|thumb),size=(0x[0-9a-f]+)\) "
                     rf"addr:0x0*{addr:x}\b")
    m = pat.search((MKDS / "config/eur/arm9/symbols.txt").read_text())
    return (m.group(1), m.group(2), m.group(3)) if m else None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--max-mm", type=int, default=8)
    ap.add_argument("--iters", type=int, default=40)
    ap.add_argument("--limit", type=int, default=50)
    ap.add_argument("--dry", action="store_true")
    args = ap.parse_args()

    done = set()
    for l in (MKDS / "ai/matched.jsonl").read_text().splitlines():
        if l.strip():
            a = json.loads(l).get("addr", "?")
            if a != "?":
                done.add(int(a, 16))

    kandidaten = []
    for f in sorted(NM.glob("*.txt")) if NM.is_dir() else []:
        try:
            addr = int(f.stem, 16)
        except ValueError:
            continue
        if addr in done:
            continue
        m = MM_RE.search(f.read_text())
        if not m:
            continue
        mm = int(m.group(1))
        if 0 < mm <= args.max_mm:
            kandidaten.append((mm, addr))
    kandidaten.sort()
    print(f"{len(kandidaten)} near-misses <= {args.max_mm} mismatches")

    fixed = 0
    for mm, addr in kandidaten[: args.limit]:
        info = sym_info(addr)
        src = MKDS / f"ai/scratch/agent_{addr:08x}.c"
        if not info or not src.is_file():
            continue
        func, mode, size = info
        print(f"  permuter-sweep: {func} @ 0x{addr:08x} ({mm} mm)...", flush=True)
        if args.dry:
            continue
        r = subprocess.run([PY, str(MKDS / "tools/permute2.py"), "--func", func,
                            "--src", str(src), "--iters", str(args.iters)],
                           capture_output=True, text=True, cwd=MKDS, timeout=1800)
        if "MATCH" in r.stdout.upper() and "match=True" in r.stdout:
            print(f"    GEVALLEN via sweep!")
            fixed += 1
    print(f"\n{fixed} near-misses gevallen; register_batch draaien om te oogsten")


if __name__ == "__main__":
    main()
