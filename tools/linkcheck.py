#!/usr/bin/env python3
"""linkcheck.py — WRONG-DEST-poort (sm64ds-stijl).

Het byte-orakel wildcardt relocatie-slots, dus een aanroep naar de VERKEERDE
functie met dezelfde vorm slaagt toch. linkcheck compileert de kandidaat, leest
de relocaties uit het object (welk symbool op welke offset), en verifieert per
reloc dat het doeladres van dat symbool GELIJK is aan wat de MKDS-config
(relocs.txt) op diezelfde ROM-offset registreert.

  tools/linkcheck.py --src cand.c --func NAAM [--module ov003 --addr 0x.. --size 0x..]
Exit 0 = alle relocs kloppen, 1 = WRONG-DEST, 2 = fout.
"""
import argparse
import io
import pathlib
import re
import subprocess
import sys
import tempfile

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent.parent.parent / "st/.venv/lib/python3.14/site-packages"))
from elftools.elf.elffile import ELFFile

MKDS = pathlib.Path(__file__).resolve().parent.parent
CONFIG = MKDS / "config/eur/arm9"
ST = MKDS.parent / "st"
WINE = "/opt/homebrew/bin/wine"
MWCC = ST / "tools/mwccarm/1.2/sp2p3/mwccarm.exe"
CC_FLAGS = ("-O4,p -enum int -lang c99 -char signed -interworking -proc arm946e "
            "-gccext,on -msgstyle gcc").split()
SYM_RE = re.compile(r"(\S+) kind:function\((arm|thumb)(?:,size=(0x\w+))?\) addr:(0x\w+)")
RELOC_RE = re.compile(r"from:(0x\w+)\s+kind:(\S+)\s+to:(0x\w+)")


def all_symbols():
    """naam -> addr over arm9 + itcm + overlays."""
    out = {}
    files = [CONFIG / "symbols.txt"]
    for extra in ("itcm", "dtcm"):
        p = CONFIG / extra / "symbols.txt"
        if p.is_file():
            files.append(p)
    for ov in sorted((CONFIG / "overlays").glob("*")):
        if (ov / "symbols.txt").is_file():
            files.append(ov / "symbols.txt")
    anyf = re.compile(r"(\S+) kind:\S+ addr:(0x\w+)")
    for f in files:
        for line in f.read_text().splitlines():
            m = anyf.match(line)
            if m:
                out.setdefault(m.group(1), int(m.group(2), 16))
    return out


def config_relocs():
    """from-offset -> to-addr uit de MKDS-config."""
    out = {}
    for f in [CONFIG / "relocs.txt"] + [ov / "relocs.txt" for ov in (CONFIG / "overlays").glob("*")]:
        if f.is_file():
            for line in f.read_text().splitlines():
                m = RELOC_RE.match(line)
                if m:
                    out[int(m.group(1), 16)] = int(m.group(3), 16)
    return out


def find_func(name, module):
    files = [("arm9", CONFIG / "symbols.txt")]
    for ov in sorted((CONFIG / "overlays").glob("*")):
        files.append((ov.name, ov / "symbols.txt"))
    for mod, f in files:
        if module and mod != module:
            continue
        for line in f.read_text().splitlines():
            m = SYM_RE.match(line)
            if m and m.group(1) == name and m.group(3):
                return mod, int(m.group(4), 16), int(m.group(3), 16), m.group(2)
    return None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--src", type=pathlib.Path, required=True)
    ap.add_argument("--func", required=True)
    ap.add_argument("--module")
    ap.add_argument("--addr", type=lambda x: int(x, 16))
    ap.add_argument("--size", type=lambda x: int(x, 16))
    args = ap.parse_args()

    info = find_func(args.func, args.module)
    if info:
        _mod, addr, size, mode = info
    else:
        addr, size, mode = args.addr, args.size, "arm"
    if addr is None:
        print("! geef --addr/--size als de functie nog niet in config staat"); sys.exit(2)

    syms = all_symbols()
    creloc = config_relocs()

    # tempdir BINNEN de repo: de wibo-container mount alleen het repo-pad,
    # een /var/folders-tempdir bestaat daar niet
    with tempfile.TemporaryDirectory(dir=str(MKDS / "build")) as td:
        out_o = pathlib.Path(td) / "o.o"
        extra = ["-thumb"] if mode == "thumb" else []
        # wibo-backend (MKDS_CC=wibo): ~5x sneller dan wine — wine gaf onder
        # parallelle belasting 150s+ timeouts in de register-poort
        import os
        if os.environ.get("MKDS_CC") == "wibo":
            mwcc_rel = MKDS / "tools/mwccarm/1.2/sp2p3/mwccarm.exe"
            mwcc = mwcc_rel if mwcc_rel.is_file() else MWCC
            cmd = ["docker", "exec", "-w", str(MKDS),
                   os.environ.get("MKDS_WIBO_CONTAINER", "mkds-cc"),
                   "qemu-i386-static", "/usr/local/bin/wibo-i686", str(mwcc)]
        else:
            cmd = [WINE, str(MWCC)]
        r = subprocess.run([*cmd, *CC_FLAGS, *extra, "-c", str(args.src), "-o", str(out_o)],
                           capture_output=True, cwd=MKDS, timeout=180)
        if not out_o.is_file():
            print("! compile faalde"); sys.exit(2)
        obj = out_o.read_bytes()

    elf = ELFFile(io.BytesIO(obj))
    symtab = elf.get_section_by_name(".symtab")
    fsym = next((s for s in symtab.iter_symbols() if s.name == args.func), None)
    if not fsym:
        print("! functiesymbool mist in object"); sys.exit(2)
    val = fsym["st_value"] & ~1
    shndx = fsym["st_shndx"]

    # THUMB-BIT-poort (InitializePrepareBackup-les 2026-07-20): een thumb-
    # functie wiens object-symbool als arm oogt laat mwld caller-BLX'en naar
    # BL collapsen -> 1-byte ROM-diff diep in een gap. Config-modus is de
    # waarheid; het object moet 'm dragen (thumb = st_value bit0 of een
    # $t-mapping op de functie-offset).
    if mode == "thumb":
        has_tbit = bool(fsym["st_value"] & 1)
        has_tmap = any(s.name == "$t" and (s["st_value"] & ~1) == val and
                       s["st_shndx"] == shndx for s in symtab.iter_symbols())
        if not (has_tbit or has_tmap):
            print(f"! THUMB-BIT ontbreekt op {args.func} in het object "
                  f"(config zegt thumb) — mwld zou BLX->BL collapsen")
            sys.exit(1)

    problems, checked = [], 0
    for rs in elf.iter_sections():
        if rs.header["sh_type"] not in ("SHT_REL", "SHT_RELA") or rs.header["sh_info"] != shndx:
            continue
        symsec = elf.get_section(rs.header["sh_link"])
        for rel in rs.iter_relocations():
            off = rel["r_offset"]
            if not (val <= off < val + size):
                continue
            tgt_sym = symsec.get_symbol(rel["r_info_sym"]).name
            if not tgt_sym:
                continue
            rom_off = addr + (off - val)
            want = creloc.get(rom_off)
            have = syms.get(tgt_sym)
            checked += 1
            if want is None:
                continue  # config kent deze offset niet als reloc (bv. pc-pool binnen functie)
            if have is None:
                problems.append(f"  0x{rom_off:08x}: kandidaat verwijst naar '{tgt_sym}' "
                                f"(onbekend symbool); ROM gaat naar 0x{want:08x}")
            elif (have & ~1) != (want & ~1):
                # thumb-bit maskeren: een load-reloc naar een thumb-functie heeft de
                # thumb-bit gezet (odd) terwijl symbols.txt het even adres geeft; dat is
                # geen wrong-dest. Alleen echte adresverschillen (>1) zijn problemen.
                right = next((n for n, a in syms.items() if (a & ~1) == (want & ~1)), f"0x{want:08x}")
                problems.append(f"  0x{rom_off:08x}: kandidaat roept '{tgt_sym}' (0x{have:08x}) "
                                f"maar ROM gaat naar '{right}' (0x{want:08x})")

    if problems:
        print(f"WRONG-DEST: {len(problems)} verkeerde reloc-doel(en) van {checked} gecheckt:")
        print("\n".join(problems))
        sys.exit(1)
    print(f"LINK OK: {checked} reloc-doelen kloppen met de config")
    sys.exit(0)


if __name__ == "__main__":
    main()
