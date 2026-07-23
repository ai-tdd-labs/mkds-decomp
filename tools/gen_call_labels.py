#!/usr/bin/env python3
"""gen_call_labels.py — genereer modus-labels op call-sites met foute mapping.

mwldarm's -interworking beslist BLX-vs-BL-vs-veneer op de modus van de
CALL-SITE volgens de $t/$a/$d mapping-symbolen in de objecten. dsd emit $t/$a
op functiestarts en $d op pools, maar GEEN hervattende $t na een pool midden in
een functie -> call-sites daarna zijn 'data' voor mwld -> veneers/BL-vs-BLX.

relocs.txt BEWIJST de modus van elke call-site (thumb_call* = thumb caller,
arm_call*/arm_branch = arm caller). Deze tool leest de mapping-symbolen uit de
gedelinkte gap-objecten, zoekt call-sites waarvan het dichtstbijzijnde
voorafgaande mapping-symbool NIET de bewezen modus geeft, en voegt daar een
kind:label(modus) toe in symbols.txt. Configdata afgeleid van configdata.

  tools/gen_call_labels.py [--apply]
"""
import argparse
import bisect
import io
import pathlib
import re
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent.parent.parent / "st/.venv/lib/python3.14/site-packages"))
from elftools.elf.elffile import ELFFile

MKDS = pathlib.Path(__file__).resolve().parent.parent
CONFIG = MKDS / "config/eur/arm9"
DELINKS = MKDS / "build/eur/delinks"

RELOC_RE = re.compile(r"from:(0x\w+)\s+kind:(\w+)\s+to:")
ADDR_RE = re.compile(r"addr:(0x\w+)")

CALLER_MODE = {"thumb_call": "thumb", "thumb_call_arm": "thumb",
               "arm_call": "arm", "arm_call_thumb": "arm", "arm_branch": "arm"}
GAP_MOD = {"main": "arm9", "itcm": "itcm", "dtcm": "dtcm"}


def module_dirs():
    out = {"arm9": CONFIG}
    for extra in ("itcm", "dtcm"):
        if (CONFIG / extra / "symbols.txt").is_file():
            out[extra] = CONFIG / extra
    for ov in sorted((CONFIG / "overlays").glob("ov*")):
        out[ov.name] = ov
    return out


def mapping_table():
    """module -> gesorteerde [(vma, modus)] uit alle gap-objecten ($t=thumb, $a=arm, $d=data)."""
    base_re = re.compile(r"_dsd_gap@(\w+?)_\d+\.o")
    tables = {}
    for p in sorted(DELINKS.rglob("*.o")):
        m = base_re.match(p.name)
        mod = GAP_MOD.get(m.group(1), m.group(1)) if m else None
        elf = ELFFile(io.BytesIO(p.read_bytes()))
        st = elf.get_section_by_name(".symtab")
        if not st:
            continue
        # sectiebasis-VMA's: dsd-gap-secties hebben addr 0; leid VMA af via een
        # bekend config-symbool per sectie -> gebruik symbols met addr in naam
        sec_vma = {}
        named = []
        for s in st.iter_symbols():
            if s['st_shndx'] == 'SHN_UNDEF' or not isinstance(s['st_shndx'], int):
                continue
            mm = re.search(r"_(0[12][0-9a-f]{6})$", s.name or "", re.I)
            if mm and s['st_info']['type'] in ('STT_FUNC', 'STT_OBJECT'):
                vma = int(mm.group(1), 16)
                sec_vma.setdefault(s['st_shndx'], vma - s['st_value'])
            if s.name in ("$t", "$a", "$d"):
                named.append((s['st_shndx'], s['st_value'], s.name))
        if mod is None:
            # TU-objecten: module onbekend; sla over (gaps dekken onontgonnen code)
            continue
        t = tables.setdefault(mod, [])
        for shndx, val, name in named:
            base = sec_vma.get(shndx)
            if base is None:
                continue
            t.append((base + val, {"$t": "thumb", "$a": "arm", "$d": "data"}[name]))
    for mod in tables:
        tables[mod].sort()
    return tables


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--apply", action="store_true")
    args = ap.parse_args()

    maps = mapping_table()
    tot = 0
    for mod, d in module_dirs().items():
        relfile = d / "relocs.txt"
        symfile = d / "symbols.txt"
        if not relfile.is_file() or not symfile.is_file() or mod not in maps:
            continue
        table = maps[mod]
        addrs = [a for a, _ in table]

        def mode_at(a):
            i = bisect.bisect_right(addrs, a) - 1
            return table[i][1] if i >= 0 else None

        lines = symfile.read_text().splitlines()
        have = set()
        for line in lines:
            m = ADDR_RE.search(line)
            if m and " kind:label(" in line:
                have.add(int(m.group(1), 16))

        new = {}
        for line in relfile.read_text().splitlines():
            m = RELOC_RE.match(line)
            if not m:
                continue
            want = CALLER_MODE.get(m.group(2))
            if not want:
                continue
            site = int(m.group(1), 16) & ~1
            if site in have or site in new:
                continue
            if mode_at(site) != want:
                new[site] = want

        if not new:
            continue
        tot += len(new)
        print(f"  {mod}: {len(new)} call-sites met foute/ontbrekende modus-mapping")
        if args.apply:
            todo = sorted((a, f".L_{a:08x} kind:label({md}) addr:0x{a:08x}")
                          for a, md in new.items())
            out = []
            for line in lines:
                m = ADDR_RE.search(line)
                a = int(m.group(1), 16) if m else None
                while todo and a is not None and todo[0][0] < a:
                    out.append(todo.pop(0)[1])
                out.append(line)
            out.extend(e[1] for e in todo)
            symfile.write_text("\n".join(out) + "\n")

    print(f"totaal: {tot}{' toegevoegd' if args.apply else ' (dry-run, --apply om te schrijven)'}")


if __name__ == "__main__":
    main()
