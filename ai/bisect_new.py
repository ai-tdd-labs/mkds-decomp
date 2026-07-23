#!/usr/bin/env python3
"""bisect_new.py — vind welke van de nieuw-geregistreerde TU's de ROM-layout
breken, via klassieke bisectie over de quarantaine (niet via byte-diff-mapping,
die bij een globale shift ALLES aanwijst).

Basis-quarantaine = ai/hangin_quarantine.txt bij start (blijft altijd erin).
Kandidaten = argv-adressen. Resultaat: boosdoeners blijven in quarantaine,
de rest draait mee; eindstand wordt geprint en de ROM is groen.
"""
import pathlib
import subprocess
import sys

MKDS = pathlib.Path(__file__).resolve().parent.parent
QUAR = MKDS / "ai/hangin_quarantine.txt"
PY = str(MKDS.parent / "st/.venv/bin/python")

base = {l.strip() for l in QUAR.read_text().splitlines() if l.strip()}
cands = [a for a in sys.argv[1:] if a not in base]
print(f"basis-quarantaine {len(base)}, kandidaten {len(cands)}", flush=True)


def build_ok(excluded):
    QUAR.write_text("\n".join(sorted(base | set(excluded))) + "\n")
    subprocess.run([PY, str(MKDS / "tools/hangin.py"), "--generate"],
                   cwd=MKDS, capture_output=True, timeout=600)
    r = subprocess.run(["bash", "build.sh"], cwd=MKDS, capture_output=True,
                       text=True, timeout=900)
    ok = "OK ===" in r.stdout
    print(f"  build ({len(excluded)} uitgesloten): {'OK' if ok else 'BREEKT'}",
          flush=True)
    if not ok:
        print("    " + "\n    ".join(r.stdout.strip().splitlines()[-3:]), flush=True)
    return ok


bad = []
while True:
    pool = [c for c in cands if c not in bad]
    if build_ok(bad):
        break  # alles behalve bad zit erin en de ROM is groen
    cur = pool
    while len(cur) > 1:
        mid = len(cur) // 2
        left, right = cur[:mid], cur[mid:]
        # test: left actief, right (+bad) uitgesloten
        if build_ok(right + bad):
            cur = right   # left is onschuldig -> boosdoener zit in right
        else:
            cur = left
    bad.append(cur[0])
    print(f"BOOSDOENER: {cur[0]}", flush=True)

print(f"\nklaar: {len(bad)} boosdoener(s): {bad}", flush=True)
print(f"groen met {len(cands) - len(bad)} nieuwe TU's erbij", flush=True)
