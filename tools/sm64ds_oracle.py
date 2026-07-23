#!/usr/bin/env python3
"""sm64ds_oracle.py — oracle-shim: permute2.py draaien tegen ../sm64ds-decomp.

Zelfde interface als aimatch (compile_src / extract_func / compare /
find_symbol / target_bytes), maar gebonden aan de sm64ds match-keten:
  * compiler: sm64ds tools/mwccarm/1.2/sp2p3/mwccarm.exe (wine-wrapper)
  * doel-bytes: extracted/arm9_dec.bin of overlay via hun modules-helper
  * symbool-info: nearmiss/db.jsonl (naam -> module/addr/size)

extract_func en compare zijn oracle-agnostisch en komen uit aimatch.
Pad instelbaar via SM64DS_ROOT (default: ../sm64ds-decomp naast mkds).
"""
import json
import os
import pathlib
import subprocess
import sys

MKDS = pathlib.Path(__file__).resolve().parent.parent
SM64 = pathlib.Path(os.environ.get("SM64DS_ROOT", MKDS.parent / "sm64ds-decomp"))
MW = SM64 / "tools" / "mwccarm"
LICENSE = MW / "license.dat"
ARM9 = SM64 / "extracted" / "arm9_dec.bin"
ARM9_BASE = 0x02004000
NEARMISS = SM64 / "nearmiss" / "db.jsonl"

# zelfde vlaggen als sm64ds tools/match.py DEFAULT_FLAGS
CC_FLAGS = ("-O4,p -enum int -lang c99 -char signed -interworking -proc arm946e "
            "-gccext,on -msgstyle gcc")

sys.path.insert(0, str(MKDS / "tools"))
from aimatch import extract_func, compare  # noqa: E402  (oracle-agnostisch)


def find_symbol(name, module=None):
    """(module, mode, addr, size) uit de near-miss-db; mode is altijd arm daar."""
    if not NEARMISS.is_file():
        return None
    for line in NEARMISS.read_text().splitlines():
        try:
            r = json.loads(line)
        except json.JSONDecodeError:
            continue
        if r.get("name") != name:
            continue
        if module and r.get("module") != module:
            continue
        return r["module"], "arm", int(r["addr"], 16), int(r["size"])
    return None


def _module_bin(module):
    if module == "arm9":
        return ARM9, ARM9_BASE
    # overlay: resolutie via sm64ds' eigen modules-helper (zoals match.py doet)
    sys.path.insert(0, str(SM64 / "tools"))
    import modules as MOD
    for mod in MOD.modules():
        label = "arm9" if mod["name"] == "main" else mod["name"]
        if label == module:
            return mod["bin"], mod["base"]
    raise SystemExit(f"sm64ds module {module} niet gevonden")


def target_bytes(module, addr, size):
    binpath, base = _module_bin(module)
    data = pathlib.Path(binpath).read_bytes()
    off = addr - base
    if off < 0 or off + size > len(data):
        raise SystemExit(f"{module}: 0x{addr:x}+0x{size:x} buiten bereik (base 0x{base:x})")
    return data[off:off + size]


CC_BACKEND = os.environ.get("SM64DS_CC", "wibo")
WIBO_CONTAINER = os.environ.get("MKDS_WIBO_CONTAINER", "mkds-cc")


def compile_src(src, out_o, mode="arm", mwcc=None):
    flags = CC_FLAGS
    try:
        if pathlib.Path(src).read_text().startswith("//cpp"):
            flags = flags.replace("-lang c99", "-lang c++")
    except OSError:
        pass
    extra = ["-thumb"] if mode == "thumb" else []
    env = dict(os.environ, LM_LICENSE_FILE=str(LICENSE))
    if CC_BACKEND == "wibo":
        # dezelfde wibo-container als mkds; de container mount de hele
        # ai-assisted-decomp op hetzelfde absolute pad, dus de gevendorde
        # echte PE (mkds/tools/mwccarm) + tmp-paden resolven ongewijzigd.
        exe = MKDS / "tools" / "mwccarm" / (mwcc or "1.2/sp2p3") / "mwccarm.exe"
        cc = ["docker", "exec", WIBO_CONTAINER,
              "qemu-i386-static", "/usr/local/bin/wibo-i686", str(exe)]
        src = pathlib.Path(src).resolve()
    else:
        # sm64ds' eigen wine-wrapper-script (traag, maar geen docker nodig)
        cc = [str(MW / (mwcc or "1.2/sp2p3") / "mwccarm.exe")]
    cmd = [*cc, *flags.split(), *extra, "-c", str(src), "-o", str(out_o)]
    try:
        r = subprocess.run(cmd, capture_output=True, text=True, env=env, timeout=120)
    except subprocess.TimeoutExpired:
        return False
    out_o = pathlib.Path(out_o)
    if r.returncode != 0 or not out_o.is_file():
        if not os.environ.get("AIMATCH_QUIET"):
            noise = ("fixme:", "err:environ", "wow64", "wineserver")
            err = "\n".join(l for l in (r.stdout + r.stderr).splitlines()
                            if l.strip() and not any(n in l for n in noise))
            print(f"! sm64ds compile faalde:\n{err[:800]}")
        return False
    return True
