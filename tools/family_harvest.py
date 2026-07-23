#!/usr/bin/env python3
"""family_harvest.py — laag 0 van de trechter: familie-klonen (geen model).

Voor elke recent gematchte functie met een scratch-bron: probeer 'm als
coddog_pool-sjabloon — siblings met identiek skelet die alleen in pool-woorden
verschillen vallen voor ~2s/stuk, zonder één agent of token. Gemeten (2026-07-15):
~75 functies in één sessie zo gematcht.

  tools/family_harvest.py [--recent 100] [--limit-per 20]
Draai VOOR elke agent-golf: alles wat hier valt hoeft nooit een pen te kosten.
"""
import argparse
import json
import pathlib
import subprocess

MKDS = pathlib.Path(__file__).resolve().parent.parent
PY = str(MKDS.parent / "st/.venv/bin/python")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--recent", type=int, default=100,
                    help="probeer de laatste N gematchte als sjabloon")
    ap.add_argument("--limit-per", type=int, default=20)
    args = ap.parse_args()

    rows = [json.loads(l) for l in
            (MKDS / "ai/matched.jsonl").read_text().splitlines() if l.strip()]
    templates = [r for r in rows if r.get("scratch") and r.get("addr", "?") != "?"]
    templates = templates[-args.recent:]
    print(f"{len(templates)} sjabloon-kandidaten (laatste {args.recent} matches)")

    tot = 0
    for r in templates:
        p = subprocess.run([PY, str(MKDS / "tools/coddog_pool.py"),
                            "--template", r["addr"], "--limit", str(args.limit_per)],
                           capture_output=True, text=True, cwd=MKDS, timeout=600)
        # coddog_pool rapporteert zelf zijn matches; tel ze
        n = p.stdout.count("MATCH")
        if n:
            print(f"  {r['func']} ({r['addr']}): {n} sibling(s) gekloond")
            tot += n
    print(f"\nlaag 0 klaar: {tot} functies via klonen; register_batch draaien om te oogsten")


if __name__ == "__main__":
    main()
