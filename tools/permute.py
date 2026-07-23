#!/usr/bin/env python3
"""permute.py — lichte bronvorm-permuter voor de near-miss-staart.

Neemt een bijna-matchende kandidaat en past automatisch broncode-mutaties toe die
mwccarm's registerallocatie/emissie beinvloeden zonder de semantiek te wijzigen,
hercompileert via aimatch, en houdt de laagste-divergentie-versie. Voor de
register-coloring-muur die de gewone loop niet kraakt.

Mutaties (semantiek-behoudend):
- lokale declaraties herordenen (kleurt callee-saved registers anders)
- `x = a; if(!c) x = b;`  <->  ternary
- tussen-variabele introduceren/elimineren voor een deref
- statement-paren omwisselen waar onafhankelijk

  tools/permute.py --src cand.c --func NAAM [--module .. --addr .. --size ..] [--iters 200]
"""
import argparse
import itertools
import pathlib
import re
import subprocess
import sys

MKDS = pathlib.Path(__file__).resolve().parent.parent
AIMATCH = MKDS / "tools/aimatch.py"
PY = str(MKDS.parent / "st/.venv/bin/python")


def score(src_text, func, module, addr, size, tmp):
    tmp.write_text(src_text)
    cmd = [PY, str(AIMATCH), "--src", str(tmp), "--func", func, "--quiet"]
    if module:
        cmd += ["--module", module]
    if addr:
        cmd += ["--addr", hex(addr)]
    if size:
        cmd += ["--size", hex(size)]
    r = subprocess.run(cmd, capture_output=True, text=True, cwd=MKDS, timeout=180)
    m = re.search(r"mismatches=(\d+)/(\d+)", r.stdout)
    if "match=True" in r.stdout:
        return 0
    return int(m.group(1)) if m else 9999


DECL_RE = re.compile(r"^\s+[A-Za-z_][\w\s\*]*?[\*\s]\w+\s*;\s*$")


def decl_reorder_variants(text):
    """Herorden lokale, niet-geinitialiseerde declaraties (elk type, ook pointers)."""
    lines = text.split("\n")
    # alleen declaraties (geen toewijzing, geen aanroep, geen control-flow)
    decl_idx = [i for i, l in enumerate(lines)
                if DECL_RE.match(l) and "=" not in l and "(" not in l
                and not re.search(r"\b(return|if|for|while|else)\b", l)]
    if not (2 <= len(decl_idx) <= 7):
        return
    block = [lines[i] for i in decl_idx]
    for perm in itertools.permutations(range(len(block))):
        if perm == tuple(range(len(block))):
            continue
        new = lines[:]
        for slot, src in zip(decl_idx, perm):
            new[slot] = block[src]
        yield "\n".join(new)


def stmt_swap_variants(text):
    """Wissel opeenvolgende onafhankelijke toewijzings-statements om."""
    lines = text.split("\n")
    for i in range(len(lines) - 1):
        a, b = lines[i].strip(), lines[i + 1].strip()
        # alleen simpele `x = ...;`-paren die geen gemeenschappelijke var lijken te delen
        if (re.match(r"^[\w\->\.\[\]]+ = .+;$", a) and re.match(r"^[\w\->\.\[\]]+ = .+;$", b)
                and "(" not in a and "(" not in b):
            lhs_a = a.split("=")[0].strip()
            if lhs_a not in b:
                new = lines[:]
                new[i], new[i + 1] = lines[i + 1], lines[i]
                yield "\n".join(new)


def all_variants(text):
    yield from decl_reorder_variants(text)
    yield from stmt_swap_variants(text)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--src", type=pathlib.Path, required=True)
    ap.add_argument("--func", required=True)
    ap.add_argument("--module")
    ap.add_argument("--addr", type=lambda x: int(x, 16))
    ap.add_argument("--size", type=lambda x: int(x, 16))
    ap.add_argument("--iters", type=int, default=200)
    args = ap.parse_args()

    base = args.src.read_text()
    tmp = MKDS / "ai/scratch/_perm.c"
    best_txt, best = base, score(base, args.func, args.module, args.addr, args.size, tmp)
    print(f"start-divergentie: {best}")
    if best == 0:
        print("al een match."); return

    tried = 0
    for variant in all_variants(base):
        if tried >= args.iters:
            break
        tried += 1
        s = score(variant, args.func, args.module, args.addr, args.size, tmp)
        if s < best:
            best, best_txt = s, variant
            print(f"  verbeterd -> {s} (variant {tried})")
            if s == 0:
                break
    tmp.unlink(missing_ok=True)

    if best == 0:
        out = args.src.with_name(args.src.stem + "_permuted.c")
        out.write_text(best_txt)
        print(f"\nMATCH gevonden! opgeslagen in {out.name}")
    else:
        print(f"\nbeste na {tried} varianten: divergentie {best} (geen match; permuter uitgeput)")
        print("=> waarschijnlijk echte floor (base-materialisatie / scheduling) -> hand-fix")


if __name__ == "__main__":
    main()
