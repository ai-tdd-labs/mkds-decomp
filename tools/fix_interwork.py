#!/usr/bin/env python3
"""fix_interwork.py — corrigeer mwldarm's overlay-verwarde thumb-bits.

mwldarm's -interworking-pass bepaalt bij ABS32 (kind:load) op ADRES of het doel
thumb is. MKDS' ov000/1/2 overlappen op 0x02180cc0+, dus de linker kan een
thumb-regio van de VERKEERDE overlay zien en een spurieuze +1 toevoegen (of een
echte +1 missen). Deze tool herberekent per kind:load-reloc de verwachte waarde
uit de dsd-config zelf:

    verwacht = adres van doelsymbool in de geannoteerde module
               | 1  als dat symbool daar een thumb-functie is

Bij ambigue relocs (module:overlays(a,b,...)) worden alle kandidaten berekend;
als er meerdere verschillende waarden mogelijk zijn en één gelijk is aan de
originele ROM-bytes, kiezen we die en loggen de disambiguatie als suggestie.
Patcht alleen slots waar gebouwd != verwacht. Rapporteert apart de slots waar
verwacht != origineel (echte configfouten — NIET weggepoetst).

  tools/fix_interwork.py [--apply]
"""
import argparse
import pathlib
import re
import struct

MKDS = pathlib.Path(__file__).resolve().parent.parent
CONFIG = MKDS / "config/eur/arm9"
BUILD = MKDS / "build/eur/build"
EXTRACT = MKDS / "extract/eur"

RELOC_RE = re.compile(r"from:(0x\w+)\s+kind:load\s+to:(0x\w+)\s+module:(\S+)(?:\s+addend:(-?\w+))?")
SYM_RE = re.compile(r"(\S+) kind:(function|data|label)(?:\(([^)]*)\))? addr:(0x\w+)")

MODULES = {}  # naam -> (binpad_build, binpad_orig, basisadres)


def module_files():
    out = {"arm9": (BUILD / "arm9.bin", EXTRACT / "arm9/arm9.bin", 0x02000000),
           "itcm": (BUILD / "itcm.bin", EXTRACT / "arm9/itcm.bin", 0x01FF8000)}
    for ov in sorted((CONFIG / "overlays").glob("ov*")):
        n = int(ov.name[2:])
        first = None
        for line in (ov / "delinks.txt").read_text().splitlines():
            m = re.search(r"start:(0x\w+)", line)
            if m:
                first = int(m.group(1), 16)
                break
        out[ov.name] = (BUILD / f"arm9_ov{n:03}.bin",
                        EXTRACT / f"arm9_overlays/ov{n:03}.bin", first)
    return out


def load_symbols():
    """module -> {addr: (naam, kind, is_thumb_func)}"""
    syms = {}
    mods = [("arm9", CONFIG / "symbols.txt"), ("itcm", CONFIG / "itcm/symbols.txt")]
    mods += [(ov.name, ov / "symbols.txt") for ov in sorted((CONFIG / "overlays").glob("ov*"))]
    for mod, f in mods:
        if not f.is_file():
            continue
        d = {}
        for line in f.read_text().splitlines():
            m = SYM_RE.match(line)
            if m:
                a = int(m.group(4), 16)
                thumb = m.group(2) == "function" and (m.group(3) or "").startswith("thumb")
                d[a] = (m.group(1), m.group(2), thumb)
        syms[mod] = d
    return syms


def load_relocs():
    """lijst van (bronmodule, from, to, [kandidaat-modules])"""
    out = []
    files = [("arm9", CONFIG / "relocs.txt"), ("itcm", CONFIG / "itcm/relocs.txt")]
    files += [(ov.name, ov / "relocs.txt") for ov in sorted((CONFIG / "overlays").glob("ov*"))]
    for mod, f in files:
        if not f.is_file():
            continue
        for line in f.read_text().splitlines():
            m = RELOC_RE.match(line)
            if not m:
                continue
            spec = m.group(3)
            if spec == "none":
                continue
            mm = re.match(r"overlays?\(([\d,]+)\)", spec)
            if mm:
                cands = [f"ov{int(x):03}" for x in mm.group(1).split(",")]
            elif spec in ("main", "arm9"):
                cands = ["arm9"]
            elif spec == "itcm":
                cands = ["itcm"]
            else:
                cands = [spec]
            addend = int(m.group(4), 0) if m.group(4) else 0
            out.append((mod, int(m.group(1), 16), int(m.group(2), 16) + addend, cands))
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--apply", action="store_true", help="patch de gebouwde bins")
    args = ap.parse_args()

    mods = module_files()
    syms = load_symbols()
    relocs = load_relocs()

    bins = {}
    for name, (bp, op, base) in mods.items():
        if bp.is_file() and op.is_file():
            bins[name] = [bytearray(bp.read_bytes()), op.read_bytes(), base, bp]

    stats = {"ok": 0, "gepatcht": 0, "config-fout": 0, "ambigu-onbeslist": 0}
    suggesties = []
    for srcmod, frm, to, cands in relocs:
        if srcmod not in bins:
            continue
        built, orig, base, bp = bins[srcmod]
        off = frm - base
        if not (0 <= off <= len(built) - 4) or off > len(orig) - 4:
            continue
        cur = struct.unpack_from("<I", built, off)[0]
        ow = struct.unpack_from("<I", orig, off)[0]

        vals = set()
        for c in cands:
            info = syms.get(c, {}).get(to)
            thumb = info[2] if info else False
            vals.add(to | 1 if thumb else to)
        if len(vals) == 1:
            exp = vals.pop()
        elif ow in vals:
            exp = ow  # origineel beslist tussen config-gesanctioneerde kandidaten
            suggesties.append((srcmod, frm, to, cands, ow))
        else:
            stats["ambigu-onbeslist"] += 1
            continue

        if exp != ow:
            stats["config-fout"] += 1
            if stats["config-fout"] <= 10:
                print(f"  CONFIG-FOUT {srcmod} from:0x{frm:08x} to:0x{to:08x} "
                      f"verwacht=0x{exp:08x} orig=0x{ow:08x}")
            continue
        if cur == exp:
            stats["ok"] += 1
        else:
            stats["gepatcht"] += 1
            if args.apply:
                struct.pack_into("<I", built, off, exp)

    if args.apply:
        for name, (built, orig, base, bp) in bins.items():
            bp.write_bytes(bytes(built))

    print(f"\nkind:load-relocs gecontroleerd over {len(bins)} modules:")
    for k, v in stats.items():
        print(f"  {k}: {v}")
    if suggesties:
        print(f"  ({len(suggesties)} ambigue relocs beslist via origineel; "
              f"disambiguatie-suggesties beschikbaar)")
    if not args.apply and stats["gepatcht"]:
        print("draai met --apply om te patchen")


if __name__ == "__main__":
    main()
