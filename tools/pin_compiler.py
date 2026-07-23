#!/usr/bin/env python3
"""Pin de MKDS-compiler: compileer sm64ds-gematchte bronnen met elke mwccarm-versie
en zoek de bytes terug in de MKDS-binary. Reloc-vrije functies zijn conclusief."""
import io
import pathlib
import subprocess
import sys
import tempfile

MKDS = pathlib.Path(__file__).resolve().parent
SM64 = MKDS.parent / "pokediamond"
ST = MKDS.parent / "st"
sys.path.insert(0, str(ST / ".venv/lib/python3.14/site-packages"))
from elftools.elf.elffile import ELFFile  # noqa: E402

WINE = "/opt/homebrew/bin/wine"
FLAGS = ("-O4,p -sym on -inline on,noauto -proc arm946e -msgstyle gcc -gccinc -fp soft "
         "-lang c99 -Cpp_exceptions off -i include -ir include-mw -ir arm9/lib/MSL_C/include "
         "-ir arm9/lib/libnns/include -ir arm9/lib/NitroSDK/include").split()
VERSIONS = ["1.2/base", "1.2/sp2p3", "1.2/sp3", "1.2/sp4",
            "2.0/base", "2.0/sp1", "2.0/sp2", "2.0/sp2p2"]

arm9 = (MKDS / "extract/usa/arm9/arm9.bin").read_bytes()
itcm = (MKDS / "extract/usa/arm9/itcm.bin").read_bytes()

def funcs_from_obj(obj):
    elf = ELFFile(io.BytesIO(obj))
    st_ = elf.get_section_by_name(".symtab")
    if not st_:
        return
    reloc_secs = {}
    for rs in elf.iter_sections():
        if rs.header["sh_type"] in ("SHT_REL", "SHT_RELA"):
            reloc_secs.setdefault(rs.header["sh_info"], []).append(rs)
    for s in st_.iter_symbols():
        if s["st_info"]["type"] != "STT_FUNC" or not s.name or s["st_size"] < 40:
            continue
        shndx = s["st_shndx"]
        if not isinstance(shndx, int):
            continue
        val = s["st_value"] & ~1
        size = s["st_size"]
        has_reloc = any(val <= r["r_offset"] < val + size
                        for rs in reloc_secs.get(shndx, []) for r in rs.iter_relocations())
        if has_reloc:
            continue  # alleen reloc-vrij is conclusief
        yield s.name, elf.get_section(shndx).data()[val:val + size]

def compile_src(src, version, tmpdir):
    out = pathlib.Path(tmpdir) / "o.o"
    cmd = [WINE, str(ST / "tools/sjiswrap.exe"), str(ST / f"tools/mwccarm/{version}/mwccarm.exe"),
           *FLAGS, "-c", str(src), "-o", str(out)]
    try:
        subprocess.run(cmd, capture_output=True, cwd=SM64, timeout=60)
    except (subprocess.TimeoutExpired, OSError):
        return None
    return out.read_bytes() if out.is_file() else None

candidates = sorted((SM64 / "arm9/lib/NitroSDK/src").glob("*.c"),
                    key=lambda p: p.stat().st_size)[10:35]
hits = {v: 0 for v in VERSIONS}
detail = []
with tempfile.TemporaryDirectory() as td:
    for src in candidates:
        for v in VERSIONS:
            obj = compile_src(src, v, td)
            if not obj:
                continue
            for name, code in funcs_from_obj(obj):
                if len(code) >= 40 and (code in arm9 or code in itcm):
                    hits[v] += 1
                    detail.append((v, name, len(code)))

print("treffers per compilerversie (reloc-vrije functies >= 40 bytes):")
for v in VERSIONS:
    print(f"  {v:<10} {hits[v]}")
print("\nvoorbeelden:")
for v, name, n in detail[:15]:
    print(f"  [{v}] {name} ({n} bytes)")
