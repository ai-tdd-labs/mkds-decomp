#!/usr/bin/env python3
"""aimatch.py — per-functie byte-match oracle voor MKDS (mwccarm 1.2/sp2p3, wine).

Compileert een kandidaat-C/C++ en vergelijkt de functie byte-voor-byte met de
ROM-bytes op het MKDS-adres. Relocatie-slots worden gewildcard.

  tools/aimatch.py --src cand.c --func GetDriverPlace
  tools/aimatch.py --src cand.c --func NAAM --module ov003 [--addr 0x.. --size 0x..]
  tools/aimatch.py --list-symbol NAAM
Exit: 0 = match, 1 = geen match, 2 = fout.
"""
import argparse
import io
import os
import pathlib
import re
import subprocess
import sys
import tempfile

from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB
from elftools.elf.elffile import ELFFile

ROOT = pathlib.Path(__file__).resolve().parent.parent
VERSION = os.environ.get("MKDS_VERSION", "eur")
EXTRACT = ROOT / "extract" / VERSION
CONFIG = ROOT / "config" / VERSION / "arm9"

WINE = "/opt/homebrew/bin/wine"
# Compiler backend: "wine" (default) or "wibo" (qemu-i386 + wibo in a Docker
# container — byte-identical objects, ~4x faster serial / ~9x parallel, and no
# wine fork-exhaustion). The container mounts the repo root at the SAME absolute
# path, so host paths resolve unchanged inside it.
CC_BACKEND = os.environ.get("MKDS_CC", "wine")
WIBO_CONTAINER = os.environ.get("MKDS_WIBO_CONTAINER", "mkds-cc")

# Compiler location: prefer the repo-vendored copy (tools/mwccarm/, so the repo
# is self-contained in a cloud sandbox), fall back to the sibling ../st checkout.
_MWCC_LOCAL = ROOT / "tools" / "mwccarm"
_MWCC_ST = ROOT.parent / "st" / "tools" / "mwccarm"


def mwcc_exe(version="1.2/sp2p3"):
    """Resolve mwccarm.exe for a compiler version (e.g. '1.2/sp2p3'),
    preferring the vendored copy and falling back to ../st per version."""
    rel = pathlib.Path(version) / "mwccarm.exe"
    local = _MWCC_LOCAL / rel
    return local if local.is_file() else _MWCC_ST / rel


MWCC = mwcc_exe()
# sm64ds-vlaggen (zelfde compiler-familie)
CC_FLAGS = ("-O4,p -enum int -lang c99 -char signed -interworking -proc arm946e "
            "-gccext,on -msgstyle gcc").split()
INCLUDES = ["-i", str(ROOT / "include")] if (ROOT / "include").is_dir() else []

SYM_RE = re.compile(
    r"^(?P<name>\S+)\s+kind:function\((?P<mode>arm|thumb)(?:,size=(?P<size>0x[0-9a-fA-F]+))?\)"
    r"\s+addr:(?P<addr>0x[0-9a-fA-F]+)")


def iter_modules():
    yield "arm9", CONFIG / "symbols.txt"
    for extra in ("itcm", "dtcm"):
        p = CONFIG / extra / "symbols.txt"
        if p.is_file():
            yield extra, p
    ovdir = CONFIG / "overlays"
    if ovdir.is_dir():
        for ov in sorted(ovdir.iterdir()):
            if (ov / "symbols.txt").is_file():
                yield ov.name, ov / "symbols.txt"


def find_symbol(name, module):
    for mod, symfile in iter_modules():
        if module and mod != module:
            continue
        for line in symfile.read_text().splitlines():
            m = SYM_RE.match(line)
            if m and m.group("name") == name:
                size = int(m.group("size"), 16) if m.group("size") else None
                return mod, m.group("mode"), int(m.group("addr"), 16), size
    return None


def module_binary(module):
    if module == "arm9":
        return EXTRACT / "arm9" / "arm9.bin", 0x02000000
    if module in ("itcm", "dtcm"):
        return EXTRACT / "arm9" / f"{module}.bin", _autoload_base(module)
    binpath = EXTRACT / "arm9_overlays" / f"{module}.bin"
    delinks = CONFIG / "overlays" / module / "delinks.txt"
    for line in delinks.read_text().splitlines():
        m = re.search(r"start:(0x[0-9a-fA-F]+)", line)
        if m:
            return binpath, int(m.group(1), 16)
    raise SystemExit(f"geen base voor {module}")


def _autoload_base(module):
    for line in (CONFIG / module / "delinks.txt").read_text().splitlines():
        m = re.search(r"start:(0x[0-9a-fA-F]+)", line)
        if m:
            return int(m.group(1), 16)
    raise SystemExit(f"geen base voor {module}")


def target_bytes(module, addr, size):
    binpath, base = module_binary(module)
    data = binpath.read_bytes()
    off = addr - base
    if off < 0 or off + size > len(data):
        raise SystemExit(f"{module}: 0x{addr:x}+0x{size:x} buiten bereik (base 0x{base:x})")
    return data[off:off + size]


def compile_src(src, out_o, mode="arm", mwcc=None):
    # thumb-functies vereisen -thumb, anders genereert mwcc ARM en kan er nooit
    # een byte-match zijn
    extra = ["-thumb"] if mode == "thumb" else []
    exe = MWCC if mwcc is None else mwcc_exe(mwcc)
    if CC_BACKEND == "wibo":
        cc = ["docker", "exec", WIBO_CONTAINER,
              "qemu-i386-static", "/usr/local/bin/wibo-i686", str(exe)]
        # container cwd differs from host; use absolute src so it resolves.
        src = pathlib.Path(src).resolve()
    elif CC_BACKEND == "wibo-native":
        # x86_64 Linux (cloud): wibo runs the 32-bit PE directly — no docker,
        # no qemu. Byte-identical to the wine/wibo-docker backends.
        wibo_bin = os.environ.get("MKDS_WIBO_BIN", "wibo")
        cc = [wibo_bin, str(exe)]
    else:
        cc = [WINE, str(exe)]
    cmd = [*cc, *CC_FLAGS, *extra, *INCLUDES, "-c", str(src), "-o", str(out_o)]
    r = subprocess.run(cmd, capture_output=True, text=True, cwd=ROOT, timeout=180)
    noise = ("fixme:", "err:environ", "wow64", "ZwLoadDriver", "scmdatabase", "hid:", "wineserver")
    err = "\n".join(l for l in (r.stdout + r.stderr).splitlines()
                    if l.strip() and not any(n in l for n in noise))
    if r.returncode != 0 or not out_o.is_file():
        if not os.environ.get("AIMATCH_QUIET"):
            print(f"! compile faalde:\n{err[:2500]}")
        return False
    if err.strip() and not os.environ.get("AIMATCH_QUIET"):
        print(err[:1200])
    return True


def extract_func(obj_bytes, func):
    elf = ELFFile(io.BytesIO(obj_bytes))
    symtab = elf.get_section_by_name(".symtab")
    sym = next((s for s in symtab.iter_symbols() if s.name == func), None)
    if sym is None:
        print("! symbool niet gevonden; functies in object:")
        for s in symtab.iter_symbols():
            if s["st_info"]["type"] == "STT_FUNC" and s.name:
                print("   ", s.name)
        return None, None
    shndx = sym["st_shndx"]
    if not isinstance(shndx, int):
        return None, None
    val = sym["st_value"] & ~1
    size = sym["st_size"]
    code = elf.get_section(shndx).data()[val:val + size]
    relocs = set()
    for rs in elf.iter_sections():
        if rs.header["sh_type"] in ("SHT_REL", "SHT_RELA") and rs.header["sh_info"] == shndx:
            for rel in rs.iter_relocations():
                off = rel["r_offset"]
                if val <= off < val + size:
                    relocs.add((off - val) & ~1)
    return code, relocs


def compare(target, cand, relocs, mode, addr, verbose=True):
    wc = set()
    for off in relocs:
        wc.update({off, off + 2})
    mism = []
    for off in range(0, max(len(target), len(cand)), 2):
        if off in wc:
            continue
        if target[off:off + 2] != cand[off:off + 2]:
            mism.append(off)
    if len(target) != len(cand):
        print(f"! grootteverschil: doel 0x{len(target):x}, kandidaat 0x{len(cand):x}")
    if mism and verbose:
        md = Cs(CS_ARCH_ARM, CS_MODE_THUMB if mode == "thumb" else CS_MODE_ARM)
        def dis(data):
            return {i.address - addr: f"{i.mnemonic} {i.op_str}" for i in md.disasm(data, addr)}
        td, cd = dis(target), dis(cand)
        print(f"{'off':>6} {'target':>30} | candidate")
        for off in mism[:36]:
            o = off & ~3
            print(f"0x{off:04x} {target[off:off+2].hex():>8} {td.get(o,''):>21.21} | "
                  f"{cand[off:off+2].hex():>8} {cd.get(o,''):<21.21}")
    return len(mism)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--src", type=pathlib.Path)
    ap.add_argument("--func")
    ap.add_argument("--module")
    ap.add_argument("--addr", type=lambda x: int(x, 16))
    ap.add_argument("--size", type=lambda x: int(x, 16))
    ap.add_argument("--list-symbol")
    ap.add_argument("--quiet", action="store_true")
    ap.add_argument("--mwcc", default=None, help="compilerversie, bv. 1.2/base (default 1.2/sp2p3)")
    args = ap.parse_args()

    if args.list_symbol:
        hit = find_symbol(args.list_symbol, args.module)
        if hit:
            mod, mode, addr, size = hit
            print(f"{args.list_symbol} module={mod} mode={mode} addr=0x{addr:08x} size={hex(size) if size else '?'}")
            sys.exit(0)
        print("niet gevonden"); sys.exit(2)

    if not args.src or not args.func:
        ap.error("--src en --func vereist")
    info = find_symbol(args.func, args.module)
    if info:
        mod, mode, addr, size = info
    else:
        mod, mode, addr, size = args.module, "arm", args.addr, args.size
    if args.addr is not None: addr = args.addr
    if args.size is not None: size = args.size
    if mod is None or addr is None or size is None:
        print(f"! symbool {args.func} niet gevonden; geef --module/--addr/--size"); sys.exit(2)

    target = target_bytes(mod, addr, size)
    # wibo backend: temp object must live inside the container's mounted tree
    # (same absolute path host<->container), so anchor it under the repo root.
    tmp_root = None
    if CC_BACKEND == "wibo":
        tmp_root = ROOT / ".wibo_tmp"
        tmp_root.mkdir(exist_ok=True)

    # Auto compiler-version fallback: many thumb functions were built with
    # mwccarm 1.2/base, not sp2p3 (Fable's discovery on the thumb pool). If the
    # caller pinned --mwcc, honour it; otherwise try sp2p3 then base and keep the
    # best. Prints which version matched so wave_harvest can record it in tus.txt.
    versions = [args.mwcc] if args.mwcc else ["1.2/sp2p3", "1.2/base"]

    def try_version(ver):
        with tempfile.TemporaryDirectory(dir=tmp_root) as td:
            out_o = pathlib.Path(td) / "cand.o"
            if not compile_src(args.src, out_o, mode, None if ver == "1.2/sp2p3" else ver):
                return None
            code, relocs = extract_func(out_o.read_bytes(), args.func)
        return code, relocs

    best = None  # (mism, code, relocs, ver)
    for ver in versions:
        r = try_version(ver)
        if r is None or r[0] is None:
            continue
        code, relocs = r
        mism = compare(target, code, relocs, mode, addr, verbose=False)
        if len(code) == len(target) and mism == 0:
            best = (0, code, relocs, ver); break
        if best is None or mism < best[0]:
            best = (mism, code, relocs, ver)
    if best is None:
        print("RESULT match=False mismatches=?/? (compile error)"); sys.exit(2)

    mism, code, relocs, ver = best
    if not args.quiet:
        compare(target, code, relocs, mode, addr, verbose=True)
    match = mism == 0 and len(code) == len(target)
    if match:
        vtag = f", mwcc {ver}" if ver != "1.2/sp2p3" else ""
        print(f"{args.func}: MATCH ({len(target)} bytes, {len(relocs)} reloc-slots gewildcard{vtag})")
    print(f"RESULT match={match} mismatches={mism}/{(len(target)+1)//2}"
          + (f" mwcc={ver}" if match and ver != "1.2/sp2p3" else ""))
    sys.exit(0 if match else 1)


if __name__ == "__main__":
    main()
