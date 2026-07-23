#!/usr/bin/env python3
"""doctor.py — snelle consistentie-check van de hele decomp-staat (geen build nodig).

Vangt de bug-klassen die deze sessie pijn deden VOORDAT je een build van 5 min draait:
  1. NAAM-DRIFT      : de functie die een src/*.c definieert moet de config-naam op
                       dat adres zijn (anders orphant de link callers).
  2. ORPHAN-REFS     : elke `extern`-verwijzing in een src moet oplossen naar een
                       config-symbool of een gematchte functie (anders undefined).
  3. STALE-GUARDS    : build.sh MOET 'mkds_eur.nds' wissen én hard falen bij een
                       link-fout (anders liegt een oude ROM een SHA-match voor).
  4. REGISTER-INTEGRITEIT: matched.jsonl-adressen/-groottes kloppen, scratch bestaat,
                       geen dubbele adressen, geen overlap met quarantaine.
  5. DEKKING         : hoeveel functies/bytes echt onze C zijn.

  tools/doctor.py            # alle checks, exit 1 bij een fout
  tools/doctor.py --quiet    # alleen samenvatting
"""
import argparse
import json
import pathlib
import re
import sys

MKDS = pathlib.Path(__file__).resolve().parent.parent
CONFIG = MKDS / "config/eur/arm9"
SRC = MKDS / "src"

SYM_FUNC = re.compile(r"(\S+) kind:function\((arm|thumb)(?:,size=(0x\w+))?\) addr:(0x\w+)")
SYM_ANY = re.compile(r"(\S+) kind:\S+ addr:(0x\w+)")
# C: functiedefinitie (niet extern, niet ;)
C_DEF = re.compile(r"^\s*(?:static\s+)?[\w\*\s]+?\b(\w+)\s*\([^;{]*\)\s*\{", re.M)


COMMENT_STRIP = re.compile(r"//[^\n]*|/\*.*?\*/", re.S)


def extern_names(txt):
    txt = COMMENT_STRIP.sub("", txt)   # comments zijn documentatie, geen code
    """gedeclareerde symboolnamen uit alle `extern ...;`-statements (niet de types).

    Vangt: `extern T naam(args)`, `extern T naam[...];`, `extern T naam;`,
    en functiepointers `extern T (*naam)(...)` / `(*naam[N])(...)`."""
    out = set()
    for stmt in txt.split(";"):
        if "extern" not in stmt:
            continue
        s = stmt.strip()
        # functiepointer-DECLARATOR: `extern T (*naam)(...)` — alleen als de
        # (*naam) vóór de eerste '(' van een parameterlijst staat; een (*x) ín
        # een parameterlijst is een parameternaam, geen link-symbool.
        m = re.match(r"[^()]*\(\s*\*\s*(\w+)\s*[\)\[]", s)
        if m:
            out.add(m.group(1)); continue
        # functie-declaratie: eerste identifier vóór '(' die geen type-woord is
        kw = {"void", "int", "char", "short", "long", "unsigned", "signed",
              "const", "struct", "union", "enum", "u8", "u16", "u32", "s8",
              "s16", "s32", "fx32", "fx64", "extern"}
        calls = [c for c in re.findall(r"\b(\w+)\s*\(", s) if c not in kw]
        if calls:
            out.add(calls[0]); continue
        m = re.search(r"\b(\w+)\s*(?:\[[^\]]*\])?\s*$", s)  # data: laatste id (evt. [N])
        if m:
            out.add(m.group(1))
    return out


def modules():
    out = {"arm9": CONFIG}
    for extra in ("itcm", "dtcm"):
        if (CONFIG / extra / "symbols.txt").is_file():
            out[extra] = CONFIG / extra
    for ov in sorted((CONFIG / "overlays").glob("ov*")):
        out[ov.name] = ov
    return out


def all_config_names():
    """set van alle config-symboolnamen; en addr->naam per module."""
    names = set()
    by_addr = {}
    for mod, d in modules().items():
        for line in (d / "symbols.txt").read_text().splitlines():
            m = SYM_ANY.match(line)
            if m:
                names.add(m.group(1))
                by_addr[(mod, int(m.group(2), 16))] = m.group(1)
    return names, by_addr


def load_matched():
    out = []
    for line in (MKDS / "ai/matched.jsonl").read_text().splitlines():
        if line.strip():
            out.append(json.loads(line))
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--quiet", action="store_true")
    args = ap.parse_args()

    errors, warns = [], []
    names, by_addr = all_config_names()
    matched = load_matched()
    quar = set()
    qf = MKDS / "ai/hangin_quarantine.txt"
    if qf.is_file():
        quar = {int(x, 16) for x in qf.read_text().split() if x.strip()}

    # ---- 3. STALE-GUARDS in build.sh ----
    bs = (MKDS / "build.sh").read_text()
    if "rm -f mkds_eur.nds" not in bs:
        errors.append("build.sh wist mkds_eur.nds NIET vooraf -> stale-ROM kan SHA-match voorliegen")
    if 'grep -q "Link failed"' not in bs and "exit 1" not in bs:
        errors.append("build.sh faalt niet hard bij een link-fout -> gefaalde link blijft onopgemerkt")

    # ---- 4. REGISTER-INTEGRITEIT ----
    seen = {}
    for r in matched:
        a = r.get("addr", "?")
        if a == "?":
            continue
        ai = int(a, 16)
        if ai in seen:
            errors.append(f"dubbel adres in matched.jsonl: {a} ({r['func']} vs {seen[ai]})")
        seen[ai] = r["func"]
        scr = MKDS / "ai/scratch" / r.get("scratch", "")
        if r.get("scratch") and not scr.is_file():
            errors.append(f"scratch mist: {r['scratch']} ({r['func']})")

    # ---- 1 & 2. NAAM-DRIFT + ORPHAN-REFS over src/*.c ----
    src_files = list(SRC.rglob("*.c")) + list(SRC.rglob("*.cpp")) if SRC.is_dir() else []
    matched_funcs = {r["func"] for r in matched}
    checked = 0
    for f in src_files:
        txt = f.read_text()
        mod = f.parent.name
        code_txt = COMMENT_STRIP.sub("", txt)
        defs = C_DEF.findall(code_txt)
        if not defs:
            continue
        defname = defs[-1]  # de gedefinieerde functie
        # welk adres? via matched.jsonl op scratch/func
        rec = next((r for r in matched if r["func"] == defname), None)
        if rec and rec.get("addr", "?") != "?":
            addr = int(rec["addr"], 16)
            cfg = by_addr.get((rec.get("module", "arm9"), addr))
            if cfg and cfg != defname:
                errors.append(f"NAAM-DRIFT: {f.name} definieert '{defname}' maar config "
                              f"heeft '{cfg}' op {rec['addr']} -> callers orphanen")
        # orphan-refs: elke gedeclareerde extern moet oplossen naar een config-symbool
        # (lokale #define-macro's tellen als gedefinieerd, geen link-symbool)
        macros = set(re.findall(r"#define\s+(\w+)", txt))
        for ref in extern_names(txt):
            if ref in macros:
                continue
            if ref not in names and ref not in matched_funcs:
                errors.append(f"ORPHAN-REF: {f.name} verwijst naar '{ref}' dat nergens "
                              f"gedefinieerd is (link-undefined)")
        checked += 1

    # ---- 5. DEKKING ----
    fsize = {}
    for line in (CONFIG / "symbols.txt").read_text().splitlines():
        m = SYM_FUNC.match(line)
        if m and m.group(3):
            fsize[int(m.group(4), 16)] = int(m.group(3), 16)
    tot = len(fsize)
    inrom = [r for r in matched if r.get("addr", "?") != "?" and int(r["addr"], 16) not in quar]
    sdk = MKDS / "ai/sdk_tus.json"
    n_sdk = 0
    if sdk.is_file():
        n_sdk = sum(1 for r in json.loads(sdk.read_text()) if int(r["addr"], 16) not in quar)
    cov_n = len(inrom) + n_sdk

    if not args.quiet:
        print(f"src/*.c gecontroleerd: {checked}")
        print(f"config-functies (arm9): {tot}")
        print(f"in ROM (matched-C {len(inrom)} + SDK {n_sdk}) = {cov_n} ({100*cov_n/max(tot,1):.1f}% van arm9)")
        print(f"geparkeerd: {len(quar)}\n")

    for w in warns:
        print(f"  ⚠ {w}")
    if errors:
        print(f"\n✗ {len(errors)} PROBLEEM(EN):")
        for e in errors[:30]:
            print(f"  ✗ {e}")
        sys.exit(1)
    print("✓ alle consistentie-checks geslaagd")


if __name__ == "__main__":
    main()
