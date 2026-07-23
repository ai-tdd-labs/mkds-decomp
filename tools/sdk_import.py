#!/usr/bin/env python3
"""sdk_import.py v2 — reloc-BEWUSTE SDK-import-pass.

Compileer SDK-bronnen uit pokediamond EN sm64ds met 1.2/sp2p3. Voor elke functie
(ook mét aanroepen) vergelijk de bytes met MKDS-functies van dezelfde grootte,
waarbij de relocatie-slots gewildcard worden (zoals dsd's signature-bitmask).
Een treffer = alle niet-reloc bytes gelijk op een echte MKDS-functiegrens.
"""
import io
import pathlib
import re
import struct
import subprocess
import sys
import concurrent.futures as cf

MKDS = pathlib.Path(__file__).resolve().parent.parent
POKE = MKDS.parent / "pokediamond"
SM64 = MKDS.parent / "sm64ds-decomp"
ST = MKDS.parent / "st"
sys.path.insert(0, str(ST / ".venv/lib/python3.14/site-packages"))
from elftools.elf.elffile import ELFFile  # noqa: E402

WINE = "/opt/homebrew/bin/wine"
import os
VERSION = os.environ.get("MWCC_VERSION", "1.2/sp2p3")
MWCC = ST / f"tools/mwccarm/{VERSION}/mwccarm.exe"
POKE_FLAGS = ("-O4,p -sym on -inline on,noauto -proc arm946e -msgstyle gcc -gccinc -fp soft "
              "-lang c99 -Cpp_exceptions off -i include -ir include-mw -ir arm9/lib/MSL_C/include "
              "-ir arm9/lib/libnns/include -ir arm9/lib/NitroSDK/include").split()
SM64_FLAGS = ("-O4,p -enum int -lang c99 -char signed -interworking -proc arm946e "
              "-gccext,on -msgstyle gcc").split()
CONFIG = MKDS / "config/eur/arm9"
EXTRACT = MKDS / "extract/eur"
MINSIZE = 12


def load_mkds():
    """size -> list of (naam, addr, module, bytes) voor bekende MKDS-functies."""
    mods = [("arm9", CONFIG / "symbols.txt", EXTRACT / "arm9/arm9.bin", 0x02000000)]
    for extra in ("itcm", "dtcm"):
        d = CONFIG / extra
        if (d / "symbols.txt").is_file():
            base = next((int(m.group(1), 16) for line in (d / "delinks.txt").read_text().splitlines()
                         if (m := re.search(r"start:(0x\w+)", line))), None)
            if base:
                mods.append((extra, d / "symbols.txt", EXTRACT / f"arm9/{extra}.bin", base))
    for ov in sorted((CONFIG / "overlays").glob("*")):
        if (ov / "symbols.txt").is_file():
            base = next((int(m.group(1), 16) for line in (ov / "delinks.txt").read_text().splitlines()
                         if (m := re.search(r"start:(0x\w+)", line))), None)
            if base:
                mods.append((ov.name, ov / "symbols.txt", EXTRACT / f"arm9_overlays/{ov.name}.bin", base))
    bysize = {}
    sym_re = re.compile(r"(\S+) kind:function\((arm|thumb),size=(0x\w+)\) addr:(0x\w+)")
    for name, symf, binf, base in mods:
        if not binf.is_file():
            continue
        data = binf.read_bytes()
        for line in symf.read_text().splitlines():
            m = sym_re.match(line)
            if not m:
                continue
            size, addr = int(m.group(3), 16), int(m.group(4), 16)
            if size < MINSIZE:
                continue
            off = addr - base
            if 0 <= off and off + size <= len(data):
                bysize.setdefault(size, []).append((m.group(1), addr, name, data[off:off + size]))
    return bysize


def compile_funcs(args):
    src, flags, cwd = args
    out_o = src.with_suffix(".imp.o")
    try:
        subprocess.run([WINE, str(MWCC), *flags, "-c", str(src), "-o", str(out_o)],
                       capture_output=True, cwd=cwd, timeout=90)
    except Exception:
        return []
    if not out_o.is_file():
        return []
    try:
        obj = out_o.read_bytes()
    finally:
        out_o.unlink(missing_ok=True)
    res = []
    try:
        elf = ELFFile(io.BytesIO(obj))
    except Exception:
        return []
    symtab = elf.get_section_by_name(".symtab")
    if not symtab:
        return []
    reloc_by_sec = {}
    for rs in elf.iter_sections():
        if rs.header["sh_type"] in ("SHT_REL", "SHT_RELA"):
            reloc_by_sec.setdefault(rs.header["sh_info"], []).append(rs)
    for s in symtab.iter_symbols():
        if s["st_info"]["type"] != "STT_FUNC" or not s.name or s["st_size"] < MINSIZE:
            continue
        shndx = s["st_shndx"]
        if not isinstance(shndx, int):
            continue
        val, size = s["st_value"] & ~1, s["st_size"]
        code = elf.get_section(shndx).data()[val:val + size]
        # {genormaliseerd-offset: reloc-type}; type nodig om call vs load te scheiden
        relocs = {}
        for rs in reloc_by_sec.get(shndx, []):
            for r in rs.iter_relocations():
                if val <= r["r_offset"] < val + size:
                    relocs[(r["r_offset"] - val) & ~3] = r["r_info_type"]
        res.append((s.name, code, relocs))
    return res


def words_match(a, b, relocs):
    for off in range(0, len(a), 4):
        if off in relocs:
            continue
        if a[off:off + 4] != b[off:off + 4]:
            return False
    return True


def build_jobs():
    """lijst van (bron-.c, mwcc-flags, cwd) over alle 10 donor-decomps."""
    jobs = []
    for sub in ("arm9/lib/NitroSDK/src", "arm9/lib/libnns/src", "arm9/lib/syscall"):
        for f in sorted((POKE / sub).rglob("*.c")):
            jobs.append((f, POKE_FLAGS, POKE))
    sdk_pat = re.compile(r"^(OS|MI|GX|MTX|FX|Vec3|SND|CARD|FS|CP|DC|IC|NNS|G2|G3|RTC|SPI|PXI)_")
    for f in (SM64 / "src").glob("*.c"):
        if sdk_pat.match(f.name):
            jobs.append((f, SM64_FLAGS, SM64))
    KH = MKDS.parent / "khdays"
    if KH.is_dir():
        kh_flags = ("-O4,p -sym on -proc arm946e -msgstyle gcc -gccinc -fp soft -lang c99 "
                    "-Cpp_exceptions off -i include -i libs/nitro/include -i libs/nitro").split()
        for f in sorted((KH / "libs/nitro").rglob("*.c")):
            jobs.append((f, kh_flags, KH))
    TW = MKDS.parent / "twewy"
    if TW.is_dir():
        tw_flags = ("-O4,p -sym on -proc arm946e -msgstyle gcc -gccinc -fp soft -lang c99 "
                    "-Cpp_exceptions off -i include -i libs/nitro/include").split()
        for f in sorted((TW / "libs/nitro/src").rglob("*.c")):
            jobs.append((f, tw_flags, TW))
    STP = MKDS.parent / "st"
    st_flags = ("-O4,p -enum int -char signed -proc arm946e -gccext,on -fp soft -lang c99 "
                "-Cpp_exceptions off -interworking -msgstyle gcc -gccinc "
                "-i include -i libs/nitro/include -i libs/nns/include -i libs/c/include "
                "-i libs/runtime/include").split()
    for f in sorted((STP / "libs").rglob("*.c")):
        jobs.append((f, st_flags, STP))
    PH = MKDS.parent / "ph"
    if PH.is_dir():
        for f in sorted((PH / "libs").rglob("*.c")):
            jobs.append((f, st_flags, PH))
    for nm, libsubs in (("pokeheartgold", ["lib/NitroSDK", "lib/MSL_C", "lib/syscall", "lib/NitroDWC"]),
                        ("pokeplatinum", ["lib"]),
                        ("pmd-sky", ["lib/NitroSDK", "lib/MSL_C", "lib/DSE"])):
        R = MKDS.parent / nm
        if not R.is_dir():
            continue
        fl = ["-O4,p", "-sym", "on", "-proc", "arm946e", "-msgstyle", "gcc", "-gccinc",
              "-fp", "soft", "-lang", "c99", "-Cpp_exceptions", "off"]
        for inc in ("include", "lib/include", "lib/NitroSDK/include", "lib/MSL_C/include",
                    "include/library", "include/library_tv"):
            if (R / inc).is_dir():
                fl += ["-ir", inc]
        for sub in libsubs:
            if (R / sub).is_dir():
                for f in sorted((R / sub).rglob("*.c")):
                    jobs.append((f, fl, R))
    OOE = MKDS.parent / "ooe"
    if OOE.is_dir():
        fl = ["-O4,p", "-sym", "on", "-proc", "arm946e", "-msgstyle", "gcc", "-gccinc",
              "-fp", "soft", "-lang", "c99", "-Cpp_exceptions", "off"]
        for inc in ("include", "libs/nds/include", "libs/c/include"):
            if (OOE / inc).is_dir():
                fl += ["-ir", inc]
        for sub in ("libs/nds", "libs/c"):
            for f in sorted((OOE / sub).rglob("*.c")):
                jobs.append((f, fl, OOE))
    return jobs


def main():
    print("MKDS-functies laden...")
    mkds = load_mkds()
    total = sum(len(v) for v in mkds.values())
    print(f"  {total:,} functies >= {MINSIZE} bytes\n")

    jobs = []
    for sub in ("arm9/lib/NitroSDK/src", "arm9/lib/libnns/src", "arm9/lib/syscall"):
        for f in sorted((POKE / sub).rglob("*.c")):
            jobs.append((f, POKE_FLAGS, POKE))
    sdk_pat = re.compile(r"^(OS|MI|GX|MTX|FX|Vec3|SND|CARD|FS|CP|DC|IC|NNS|G2|G3|RTC|SPI|PXI)_")
    for f in (SM64 / "src").glob("*.c"):
        if sdk_pat.match(f.name):
            jobs.append((f, SM64_FLAGS, SM64))
    # khdays: 311 NitroSDK-bronnen
    KH = MKDS.parent / "khdays"
    if KH.is_dir():
        kh_flags = ("-O4,p -sym on -proc arm946e -msgstyle gcc -gccinc -fp soft -lang c99 "
                    "-Cpp_exceptions off -i include -i libs/nitro/include -i libs/nitro").split()
        for f in sorted((KH / "libs/nitro").rglob("*.c")):
            jobs.append((f, kh_flags, KH))
    # twewy
    TW = MKDS.parent / "twewy"
    if TW.is_dir():
        tw_flags = ("-O4,p -sym on -proc arm946e -msgstyle gcc -gccinc -fp soft -lang c99 "
                    "-Cpp_exceptions off -i include -i libs/nitro/include").split()
        for f in sorted((TW / "libs/nitro/src").rglob("*.c")):
            jobs.append((f, tw_flags, TW))
    # st (dsi-era bron, toch proberen)
    STP = MKDS.parent / "st"
    st_flags = ("-O4,p -enum int -char signed -proc arm946e -gccext,on -fp soft -lang c99 "
                "-Cpp_exceptions off -interworking -msgstyle gcc -gccinc "
                "-i include -i libs/nitro/include -i libs/nns/include -i libs/c/include "
                "-i libs/runtime/include").split()
    for f in sorted((STP / "libs").rglob("*.c")):
        jobs.append((f, st_flags, STP))
    # ph
    PH = MKDS.parent / "ph"
    if PH.is_dir():
        for f in sorted((PH / "libs").rglob("*.c")):
            jobs.append((f, st_flags, PH))
    # pokeheartgold / pokeplatinum / pmd-sky (pret-stijl lib-layout)
    for nm, libsubs in (("pokeheartgold", ["lib/NitroSDK", "lib/MSL_C", "lib/syscall", "lib/NitroDWC"]),
                        ("pokeplatinum", ["lib"]),
                        ("pmd-sky", ["lib/NitroSDK", "lib/MSL_C", "lib/DSE"])):
        R = MKDS.parent / nm
        if not R.is_dir():
            continue
        fl = ["-O4,p", "-sym", "on", "-proc", "arm946e", "-msgstyle", "gcc", "-gccinc",
              "-fp", "soft", "-lang", "c99", "-Cpp_exceptions", "off"]
        for inc in ("include", "lib/include", "lib/NitroSDK/include", "lib/MSL_C/include",
                    "include/library", "include/library_tv"):
            if (R / inc).is_dir():
                fl += ["-ir", inc]
        for sub in libsubs:
            if (R / sub).is_dir():
                for f in sorted((R / sub).rglob("*.c")):
                    jobs.append((f, fl, R))
    # ooe (nds/c-libs, GameSpy overslaan: netwerkcode, andere wereld)
    OOE = MKDS.parent / "ooe"
    if OOE.is_dir():
        fl = ["-O4,p", "-sym", "on", "-proc", "arm946e", "-msgstyle", "gcc", "-gccinc",
              "-fp", "soft", "-lang", "c99", "-Cpp_exceptions", "off"]
        for inc in ("include", "libs/nds/include", "libs/c/include"):
            if (OOE / inc).is_dir():
                fl += ["-ir", inc]
        for sub in ("libs/nds", "libs/c"):
            for f in sorted((OOE / sub).rglob("*.c")):
                jobs.append((f, fl, OOE))
    print(f"{len(jobs)} bronnen compileren (10 decomp-projecten)...\n")

    hits, seen = [], set()
    near = []
    def word_score(a, b, relocs):
        tot = eq = 0
        for off in range(0, len(a), 4):
            if off in relocs:
                continue
            tot += 1
            if a[off:off+4] == b[off:off+4]:
                eq += 1
        return eq / max(tot, 1)
    with cf.ThreadPoolExecutor(max_workers=4) as ex:
        for (src, _fl, _cwd), funcs in zip(jobs, ex.map(compile_funcs, jobs)):
            for fname, code, relocs in funcs:
                cands = mkds.get(len(code))
                if not cands:
                    continue
                for mname, addr, mod, mbytes in cands:
                    if addr in seen:
                        continue
                    sc = word_score(code, mbytes, relocs)
                    if sc == 1.0:
                        hits.append((fname, mname, addr, mod, len(code), len(relocs)))
                        seen.add(addr)
                        break
                    elif sc >= 0.80 and len(code) >= 48:
                        near.append({"score": round(sc, 3), "func": fname, "mkds": mname,
                                     "addr": hex(addr), "module": mod, "size": len(code),
                                     "bron": str(src)})

    print("== RESULTAAT ==")
    print(f"byte-identieke SDK-functies in MKDS: {len(hits)}  ({sum(h[4] for h in hits):,} bytes)")
    relocful = sum(1 for h in hits if h[5] > 0)
    print(f"  waarvan mét aanroepen (reloc-bewust gevonden): {relocful}\n")
    for fname, mname, addr, mod, n, nr in sorted(hits, key=lambda x: -x[4])[:35]:
        tag = f"+{nr}reloc" if nr else "leaf"
        print(f"  {n:4} B {tag:>8}  {fname:<30} -> {mod} 0x{addr:08x} ({mname})")
    import json
    (MKDS / f"ai/sdk_import_hits_{VERSION.replace('/', '_')}.json").write_text(json.dumps(
        [{"src": f, "mkds": m, "addr": hex(a), "module": mo, "size": n, "relocs": nr}
         for f, m, a, mo, n, nr in hits], indent=1))
    near.sort(key=lambda x: -x["score"])
    dedup, seenm = [], set()
    for n in near:
        if n["addr"] not in seenm and n["addr"] not in {hex(h[2]) for h in hits}:
            dedup.append(n); seenm.add(n["addr"])
    (MKDS / "ai/sdk_nearhits.json").write_text(json.dumps(dedup[:120], indent=1))
    print(f"\n{len(hits)} treffers + {len(dedup)} bijna-treffers (>=80%) opgeslagen (compiler {VERSION})")


if __name__ == "__main__":
    main()
