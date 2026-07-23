#!/usr/bin/env python3
"""register_batch.py — auto-registrar (fase A ledger).

Scant ai/scratch/ op kandidaatbestanden waarvan de naam een adres bevat
(fam*_ADDR.c, cg_ADDR.c, ob_ADDR.c), zoekt naam+grootte+module op via het adres
in de dsd-config, her-verifieert met het orakel, en voegt bevestigde matches toe
aan ai/matched.jsonl (dedup op adres). Nul handmatig invoeren.

  tools/register_batch.py [--glob 'fam*_*.c']
"""
import argparse
import glob
import json
import pathlib
import re
import subprocess

MKDS = pathlib.Path(__file__).resolve().parent.parent
PY = str(MKDS.parent / "st/.venv/bin/python")
AIMATCH = MKDS / "tools/aimatch.py"
CONFIG = MKDS / "config/eur/arm9"
SYM_RE = re.compile(r"(\S+) kind:function\((arm|thumb),size=(0x\w+)\) addr:(0x\w+)")
ADDR_RE = re.compile(r"(?:^|_)0?x?(0[12][0-9a-fA-F]{6})", re.I)


def addr_index():
    """addr -> (naam, module, size, mode)."""
    idx = {}
    mods = [("arm9", CONFIG / "symbols.txt")]
    for extra in ("itcm", "dtcm"):
        p = CONFIG / extra / "symbols.txt"
        if p.is_file():
            mods.append((extra, p))
    for ov in sorted((CONFIG / "overlays").glob("*")):
        if (ov / "symbols.txt").is_file():
            mods.append((ov.name, ov / "symbols.txt"))
    for mod, f in mods:
        for line in f.read_text().splitlines():
            m = SYM_RE.match(line)
            if m:
                idx[int(m.group(4), 16)] = (m.group(1), mod, m.group(3), m.group(2))
    return idx


def load_done():
    done = set()
    mj = MKDS / "ai/matched.jsonl"
    if mj.is_file():
        for line in mj.read_text().splitlines():
            if line.strip():
                a = json.loads(line).get("addr", "?")
                if a != "?":
                    done.add(int(a, 16))
    return done


def verify(src, func, module, addr, size):
    cmd = [PY, str(AIMATCH), "--src", str(src), "--func", func,
           "--module", module, "--addr", hex(addr), "--size", size, "--quiet"]
    try:
        r = subprocess.run(cmd, capture_output=True, text=True, cwd=MKDS, timeout=150)
    except subprocess.TimeoutExpired:
        return None
    if "match=True" not in r.stdout:
        return False
    # WRONG-DEST-poort: bytes kunnen matchen terwijl een reloc naar het
    # verkeerde symbool wijst (oracle wildcardt slots); dat brak de ROM 4x
    # (1-2-byte diffs, elk een build-cyclus kwijt). linkcheck vangt het hier.
    try:
        lc = subprocess.run([PY, str(MKDS / "tools/linkcheck.py"), "--src", str(src),
                             "--func", func, "--module", module, "--addr", hex(addr),
                             "--size", size], capture_output=True, text=True,
                            cwd=MKDS, timeout=200)
    except subprocess.TimeoutExpired:
        # poort mag registratie vertragen, nooit de hele run laten crashen
        print(f"    WRONG-DEST-poort timeout op {func} — geweigerd (later opnieuw)")
        return False
    if lc.returncode != 0:
        print(f"    WRONG-DEST-poort weigert {func} (linkcheck exit {lc.returncode})")
        return False
    # aimatch's auto-fallback rapporteert de gebruikte compilerversie (bv.
    # mwcc=1.2/base); die moet mee het register in, anders compileert de
    # build straks met de verkeerde versie en breekt de SHA1.
    m = re.search(r"mwcc=(\S+)", r.stdout)
    return m.group(1) if m else True


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--glob", default="ai/scratch/fam*_*.c")
    args = ap.parse_args()

    idx = addr_index()
    done = load_done()
    new = []
    files = sorted(glob.glob(str(MKDS / args.glob)))
    print(f"{len(files)} kandidaatbestanden; verifiëren...\n")
    for fp in files:
        m = ADDR_RE.search(pathlib.Path(fp).stem)
        if not m:
            continue
        addr = int(m.group(1), 16)
        if addr in done:
            continue
        if addr not in idx:
            print(f"  ? {pathlib.Path(fp).name}: adres 0x{addr:08x} niet in config")
            continue
        func, module, size, mode = idx[addr]
        ok = verify(pathlib.Path(fp), func, module, addr, size)
        tag = "OK " if ok else ("timeout" if ok is None else "GEEN MATCH")
        print(f"  [{tag}] {func} @ 0x{addr:08x}")
        if ok:
            rec = {"func": func, "naam": func, "module": module,
                   "addr": hex(addr), "size": size, "bron": "family-batch",
                   "scratch": pathlib.Path(fp).name}
            if isinstance(ok, str):
                rec["mwcc"] = ok
            new.append(rec)
            done.add(addr)

    if new:
        with (MKDS / "ai/matched.jsonl").open("a") as f:
            for r in new:
                f.write(json.dumps(r) + "\n")
    print(f"\n{len(new)} nieuwe matches toegevoegd aan ai/matched.jsonl")
    print(f"totaal in register: {len(done)}")


if __name__ == "__main__":
    main()
