#!/usr/bin/env python3
"""diffmap.py — wijs de bytes waar de herbouwde ROM afwijkt toe aan de schuldige TU's.

Na een build die VERSCHIL geeft: welke functie(s) doen het? Deze tool vergelijkt
elke gebouwde module met het origineel, groepeert de afwijkende bytes, en wijst ze
toe aan de TU (matched of SDK) die dat adresbereik bezit. Classificeert:
  - LAYOUT-SHIFT : één TU heeft de verkeerde grootte -> alles erna schuift (cascade);
                   de EERSTE afwijkende TU is de boosdoener, de rest zijn slachtoffers.
  - INHOUD/RELOC : losse woorden verschillen binnen een TU (verkeerd reloc-doel).
  - GAP          : afwijking in niet-gedecompileerd gebied (call naar verschoven doel).

  tools/diffmap.py                 # rapport
  tools/diffmap.py --quarantine    # zet de eerste-orde-boosdoeners in quarantaine
"""
import argparse
import json
import pathlib
import re
import struct

MKDS = pathlib.Path(__file__).resolve().parent.parent
CONFIG = MKDS / "config/eur/arm9"
EXTRACT = MKDS / "extract/eur"
BUILD = MKDS / "build/eur/build"

MODS = {"arm9": (BUILD / "arm9.bin", EXTRACT / "arm9/arm9.bin", 0x02000000),
        "itcm": (BUILD / "itcm.bin", EXTRACT / "arm9/itcm.bin", 0x01FF8000)}
for _i in range(4):
    MODS[f"ov{_i:03}"] = (BUILD / f"arm9_ov{_i:03}.bin",
                          EXTRACT / f"arm9_overlays/ov{_i:03}.bin", None)


def ov_base(mod):
    for line in (CONFIG / "overlays" / mod / "delinks.txt").read_text().splitlines():
        m = re.search(r"start:(0x\w+)", line)
        if m:
            return int(m.group(1), 16)


def load_tus():
    tus = []
    for line in (MKDS / "ai/matched.jsonl").read_text().splitlines():
        if line.strip():
            r = json.loads(line)
            if r.get("addr", "?") != "?":
                tus.append((int(r["addr"], 16), int(r["size"], 16), r["func"],
                            r.get("module", "arm9"), "matched"))
    sf = MKDS / "ai/sdk_tus.json"
    if sf.is_file():
        for r in json.loads(sf.read_text()):
            tus.append((int(r["addr"], 16), int(r["size"], 16), r["func"], r["module"], "sdk"))
    return sorted(tus)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--quarantine", action="store_true")
    args = ap.parse_args()

    tus = load_tus()
    culprits = []
    for mod, (bp, op, base) in MODS.items():
        if not bp.is_file() or not op.is_file():
            continue
        if base is None:
            base = ov_base(mod)
        b, o = bp.read_bytes(), op.read_bytes()
        n = min(len(b), len(o))
        diffs = [i for i in range(n) if b[i] != o[i]]
        if not diffs and len(b) == len(o):
            continue
        print(f"\n== {mod}: {len(diffs)} diff-bytes, lengte {len(b)} vs {len(o)} ({len(b)-len(o):+d})")
        modtus = [t for t in tus if t[3] == mod]

        # detecteer een layout-shift: eerste plek waar b hervat = o met constante delta
        shift_at = None
        i = diffs[0] if diffs else n
        for d in range(4, 260, 4):
            if b[i:i + 48] == o[i + d:i + d + 48] or b[i + d:i + d + 48] == o[i:i + 48]:
                shift_at = base + i
                break

        def owner(va):
            for a, sz, f, m, src in modtus:
                if a <= va < a + sz:
                    return (a, sz, f, src)
            return None

        if shift_at is not None:
            ow = owner(shift_at) or next(((a, sz, f, s) for a, sz, f, m, s in modtus
                                          if a + sz <= shift_at and shift_at - (a + sz) < 0x20), None)
            print(f"  LAYOUT-SHIFT bij 0x{shift_at:08x} -> een TU heeft verkeerde grootte")
            if ow:
                print(f"    eerste boosdoener (grootte): {ow[2]} @0x{ow[0]:08x} ({ow[3]})")
                culprits.append(ow[0])
            continue

        # anders: losse afwijkende TU's (inhoud/reloc)
        bad = {}
        for va in (base + d for d in diffs):
            ow = owner(va)
            if ow:
                bad.setdefault(ow[0], ow)
            else:
                bad.setdefault(-1, ("gap",))
        real = [v for k, v in bad.items() if k != -1]
        print(f"  {len(real)} afwijkende TU('s), {'+gap-bytes' if -1 in bad else ''}")
        for a, sz, f, src in sorted(real)[:15]:
            print(f"    {f:<28} 0x{a:08x} ({src})")
            culprits.append(a)

    if args.quarantine and culprits:
        qf = MKDS / "ai/hangin_quarantine.txt"
        q = {int(x, 16) for x in qf.read_text().split() if x.strip()} if qf.is_file() else set()
        q |= set(culprits)
        qf.write_text("\n".join(f"0x{a:08x}" for a in sorted(q)) + "\n")
        print(f"\n{len(culprits)} boosdoener(s) in quarantaine gezet -> {len(q)} totaal. "
              f"Herdraai: tools/hangin.py --generate && bash build.sh")
    elif not culprits:
        print("\n✓ geen afwijkingen — ROM is byte-perfect")


if __name__ == "__main__":
    main()
