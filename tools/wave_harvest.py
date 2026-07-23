#!/usr/bin/env python3
"""wave_harvest.py — oogst een agent-golf: verifieer, registreer, repliceer, bouw, rapporteer.

Voor elk doel uit ai/wave/manifest.json:
  1. bestaat ai/scratch/agent_<addr>.c? -> orakel (aimatch) + snelle linkcheck;
  2. bij match: registreer in ai/matched.jsonl;
  3. probeer familie-replicatie (coddog_pool) op het nieuwe sjabloon;
daarna: names --record, hangin --generate, doctor, build.sh; bij byte-perfect commit
(+ optioneel push), anders diffmap-rapport en GEEN commit.

  tools/wave_harvest.py [--push]
"""
import argparse
import json
import pathlib
import subprocess
import sys

MKDS = pathlib.Path(__file__).resolve().parent.parent
PY = str(MKDS.parent / "st/.venv/bin/python")
WAVE = MKDS / "ai/wave"


def run(cmd, timeout=900):
    return subprocess.run(cmd, capture_output=True, text=True, cwd=MKDS, timeout=timeout)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--push", action="store_true")
    args = ap.parse_args()

    manifest = json.loads((WAVE / "manifest.json").read_text())
    # ROBUUST: manifest kan overschreven zijn door een tussentijdse wave_prep-run.
    # Veeg ook alle agent_*.c op die nog niet in matched.jsonl staan (adres uit
    # bestandsnaam, naam/size uit de config) — dan gaat er nooit een oogst verloren.
    import re as _re
    _have = {json.loads(l)["addr"] for l in (MKDS / "ai/matched.jsonl").read_text().splitlines()
             if l.strip() and json.loads(l).get("addr", "?") != "?"}
    _cfg = {}
    for _l in (MKDS / "config/eur/arm9/symbols.txt").read_text().splitlines():
        _m = _re.match(r"(\S+) kind:function\((arm|thumb),size=(0x\w+)\) addr:(0x\w+)", _l)
        if _m:
            _cfg[int(_m.group(4), 16)] = (_m.group(1), _m.group(3))
    _known = {int(m["addr"], 16) for m in manifest}
    for _f in sorted((MKDS / "ai/scratch").glob("agent_*.c")):
        _a = int(_f.stem.split("_")[1], 16)
        if _a in _known or f"0x{_a:08x}" in _have or _a not in _cfg:
            continue
        manifest.append({"addr": f"0x{_a:08x}", "func": _cfg[_a][0], "size": _cfg[_a][1]})
    have = {json.loads(l)["addr"] for l in (MKDS / "ai/matched.jsonl").read_text().splitlines()
            if l.strip() and json.loads(l).get("addr", "?") != "?"}

    ok, miss, absent = [], [], []
    for m in manifest:
        addr = int(m["addr"], 16)
        src = MKDS / f"ai/scratch/agent_{addr:08x}.c"
        if not src.is_file():
            absent.append(m["func"])
            continue
        r = run([PY, "tools/aimatch.py", "--src", str(src), "--func", m["func"],
                 "--module", "arm9", "--addr", m["addr"], "--size", m["size"], "--quiet"],
                timeout=180)
        if "match=True" not in r.stdout:
            miss.append(m["func"])
            continue
        lc = run([PY, "tools/linkcheck.py", "--src", str(src), "--func", m["func"],
                  "--module", "arm9", "--addr", m["addr"], "--size", m["size"]], timeout=180)
        if "WRONG-DEST" in lc.stdout:
            miss.append(f"{m['func']} (WRONG-DEST!)")
            continue
        if f"0x{addr:08x}" not in have and m["addr"] not in have:
            with (MKDS / "ai/matched.jsonl").open("a") as f:
                f.write(json.dumps({"func": m["func"], "naam": m["func"], "module": "arm9",
                                    "addr": f"0x{addr:08x}", "size": m["size"],
                                    "bron": "wave(agent)", "scratch": src.name}) + "\n")
        ok.append(m)
        print(f"  ✓ {m['func']} (match + link ok)")

    print(f"\ngeoogst: {len(ok)} | mis: {miss or '-'} | agent nog bezig/geen output: {absent or '-'}")

    # claims vrijgeven: gematcht -> done, niet gematcht -> released (append-log)
    okf = {m["func"] for m in ok}
    with (MKDS / "ai/claims.jsonl").open("a") as cf:
        for m in manifest:
            st = "done" if m["func"] in okf else "released"
            cf.write(json.dumps({"func": m["func"], "addr": m["addr"],
                                 "who": "harvest", "status": st}) + "\n")

    # familie-replicatie op de nieuwe sjablonen
    total_rep = 0
    for m in ok:
        r = run([PY, "tools/coddog_pool.py", "--template", m["addr"], "--size", m["size"],
                 "--limit", "30"], timeout=600)
        for line in r.stdout.splitlines():
            if "gematcht in" in line:
                total_rep += int(line.split("/")[0].strip())
                print(f"  {m['func']}: {line.strip()}")
    print(f"replicaties: {total_rep}")

    if not ok and not total_rep:
        print("niets nieuws — geen build nodig")
        return

    # naamgeving + inhangen + verifiëren
    run([PY, "tools/names.py", "--record"], timeout=300)
    run([PY, "tools/funcfacts.py"], timeout=300)  # feiten-register verversen
    run([PY, "tools/hangin.py", "--generate"], timeout=300)
    b = run(["bash", "build.sh"], timeout=900)
    if "OK ===" in b.stdout:
        n = len(ok) + total_rep
        subprocess.run(["git", "add", "-A"], cwd=MKDS)
        subprocess.run(["git", "commit", "-q", "-m",
                        f"Wave: {len(ok)} sjablonen + {total_rep} replicaties byte-perfect\n\n"
                        f"Automatische golf-oogst (wave_prep/wave_harvest).\n\n"
                        f"Co-Authored-By: Claude Fable 5 <noreply@anthropic.com>"], cwd=MKDS)
        if args.push:
            subprocess.run(["git", "push", "-q", "origin", "main"], cwd=MKDS)
        print(f"\n*** BYTE-PERFECT: +{n} functies gecommit{' + gepushed' if args.push else ''} ***")
    else:
        print("\n!!! build VERSCHIL/fout — GEEN commit. Diagnose:")
        d = run([PY, "tools/diffmap.py"], timeout=300)
        print(d.stdout[-2000:])


if __name__ == "__main__":
    main()
