#!/usr/bin/env python3
"""Gerichte compiler-pin: vergelijk benoemde SDK-functies op hun MKDS-adres,
relocatie-bewust, over meerdere compilerversies."""
import io
import pathlib
import re
import subprocess
import sys
import tempfile

MKDS = pathlib.Path(__file__).resolve().parent
POKE = MKDS.parent / "pokediamond"
ST = MKDS.parent / "st"
sys.path.insert(0, str(ST / ".venv/lib/python3.14/site-packages"))
from elftools.elf.elffile import ELFFile  # noqa: E402

WINE = "/opt/homebrew/bin/wine"
FLAGS = ("-O4,p -sym on -inline on,noauto -proc arm946e -msgstyle gcc -gccinc -fp soft "
         "-lang c99 -Cpp_exceptions off -i include -ir include-mw -ir arm9/lib/MSL_C/include "
         "-ir arm9/lib/libnns/include -ir arm9/lib/NitroSDK/include").split()
VERSIONS = ["1.2/base", "1.2/sp2p3", "1.2/sp3", "1.2/sp4", "2.0/base", "2.0/sp1", "2.0/sp2p2"]

arm9 = (MKDS / "extract/eur/arm9/arm9.bin").read_bytes()

# benoemde SDK-functies in MKDS-config
targets = {}
for line in (MKDS / "config/eur/arm9/symbols.txt").read_text().splitlines():
    m = re.match(r"([A-Z][A-Za-z0-9_]+) kind:function\(arm,size=(0x\w+)\) addr:(0x\w+)", line)
    if m and m.group(1).split("_")[0] in ("OS", "MI", "FS", "SND", "GX", "MTX", "FX", "CARD"):
        targets[m.group(1)] = (int(m.group(3), 16), int(m.group(2), 16))

# vind bronbestand per functie
srcdir = POKE / "arm9/lib/NitroSDK/src"
filemap = {}
for f in srcdir.glob("*.c"):
    txt = f.read_text(errors="ignore")
    for name in targets:
        if re.search(rf"\b{name}\s*\(", txt):
            filemap.setdefault(name, f)
print(f"{len(targets)} benoemde SDK-functies, {len(filemap)} met bron in pokediamond\n")

def compile_and_extract(src, version, func, td):
    out = pathlib.Path(td) / "o.o"
    out.unlink(missing_ok=True)
    cmd = [WINE, str(ST / "tools/sjiswrap.exe"), str(ST / f"tools/mwccarm/{version}/mwccarm.exe"),
           *FLAGS, "-c", str(src), "-o", str(out)]
    try:
        subprocess.run(cmd, capture_output=True, cwd=POKE, timeout=60)
    except Exception:
        return None, None
    if not out.is_file():
        return None, None
    elf = ELFFile(io.BytesIO(out.read_bytes()))
    st_ = elf.get_section_by_name(".symtab")
    sym = next((s for s in st_.iter_symbols() if s.name == func), None)
    if not sym:
        return None, None
    shndx = sym["st_shndx"]
    if not isinstance(shndx, int):
        return None, None
    val = sym["st_value"] & ~1
    code = elf.get_section(shndx).data()[val:val + sym["st_size"]]
    relocs = set()
    for rs in elf.iter_sections():
        if rs.header["sh_type"] in ("SHT_REL", "SHT_RELA") and rs.header["sh_info"] == shndx:
            for r in rs.iter_relocations():
                if val <= r["r_offset"] < val + sym["st_size"]:
                    relocs.add((r["r_offset"] - val) & ~3)
    return code, relocs

def diff(target, cand, relocs):
    if cand is None:
        return None
    n = 0
    for off in range(0, max(len(target), len(cand)), 4):
        if off in relocs:
            continue
        if target[off:off+4] != cand[off:off+4]:
            n += 1
    if len(target) != len(cand):
        n += abs(len(target) - len(cand)) // 4
    return n

with tempfile.TemporaryDirectory() as td:
    # spreid over modules zodat we kans maken op een onderscheidende functie
    bymod = {}
    for name, src in filemap.items():
        bymod.setdefault(name.split("_")[0], []).append((name, src))
    picks = []
    for mod in sorted(bymod):
        picks.extend(bymod[mod][:3])
    header = "functie".ljust(28) + "".join(v.ljust(11) for v in VERSIONS)
    print(header)
    for name, src in picks:
        addr, size = targets[name]
        rom = arm9[addr - 0x2000000: addr - 0x2000000 + size]
        row = name.ljust(28)
        for v in VERSIONS:
            code, relocs = compile_and_extract(src, v, name, td)
            d = diff(rom, code, relocs) if code else None
            row += (("MATCH" if d == 0 else f"div{d}") if d is not None else "-").ljust(11)
        print(row)
