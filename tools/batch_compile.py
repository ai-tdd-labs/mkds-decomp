#!/usr/bin/env python3
"""batch_compile.py — compileer alle TU's uit ai/tus.txt in gebatchte wine-aanroepen.

Wine's opstartkost (~3s) domineerde de bouwtijd; mwcc accepteert meerdere bronnen
per aanroep (gemeten: 10 bestanden in 0,5s totaal). Deze tool:
  - cache-sleutel = sha1 van de bron ZONDER comments (documenteren is gratis),
  - groepeert cache-missers per mode (arm/thumb) en compileert in batches van 40
    in één wine-aanroep (cwd = tempdir; mwcc schrijft <basenaam>.o),
  - valt bij een ontbrekend object terug op een losse compile voor de foutmelding.

  tools/batch_compile.py            # gebruikt ai/tus.txt
"""
import os
import pathlib
import re
import shutil
import subprocess
import sys
import tempfile
import hashlib

MKDS = pathlib.Path(__file__).resolve().parent.parent
ST = MKDS.parent / "st"
WINE = "/opt/homebrew/bin/wine"
# Backend: MKDS_CC=wibo runs mwcc via qemu-i386+wibo in the mkds-cc container
# (repo root mounted at the SAME absolute path; ~4-8x faster than wine and no
# fork-exhaustion). Temp dirs must then live INSIDE the mount.
CC_BACKEND = os.environ.get("MKDS_CC", "wine")
WIBO_CONTAINER = os.environ.get("MKDS_WIBO_CONTAINER", "mkds-cc")


def cc_cmd(exe, workdir=None):
    """command-prefix voor de gekozen backend; workdir = cwd in de container."""
    if CC_BACKEND == "wibo":
        pre = ["docker", "exec"]
        if workdir is not None:
            pre += ["-w", str(workdir)]
        return [*pre, WIBO_CONTAINER,
                "qemu-i386-static", "/usr/local/bin/wibo-i686", str(exe)]
    return [WINE, str(exe)]
MWCC = ST / "tools/mwccarm/1.2/sp2p3/mwccarm.exe"
CFLAGS = ("-O4,p -enum int -lang c99 -char signed -interworking -proc arm946e "
          "-gccext,on -msgstyle gcc").split()
CACHE = MKDS / "build/eur/objcache"
DELINKS = MKDS / "build/eur/delinks"
BATCH = 40

COMMENT_RE = re.compile(r"//[^\n]*|/\*.*?\*/", re.S)


def code_key(src, mode):
    """sha1 van de bron zonder comments + mode: comment-edits raken de cache niet."""
    code = COMMENT_RE.sub("", pathlib.Path(src).read_text())
    return hashlib.sha1((code + "\n#mode=" + mode).encode()).hexdigest()


def main():
    CACHE.mkdir(parents=True, exist_ok=True)
    rows = []
    for line in (MKDS / "ai/tus.txt").read_text().splitlines():
        parts = line.split("\t")
        if len(parts) < 2 or not parts[0]:
            continue
        src, obj = parts[0], parts[1]
        mode = parts[2] if len(parts) > 2 and parts[2] else "arm"
        ver = parts[3] if len(parts) > 3 and parts[3] else "1.2/sp2p3"
        rows.append((MKDS / src, MKDS / "build/eur/delinks" / obj, mode, ver))

    todo = {}
    hits = 0
    for src, obj, mode, ver in rows:
        key = code_key(src, mode + "|" + ver)
        cobj = CACHE / f"{key}.o"
        if cobj.is_file():
            obj.parent.mkdir(parents=True, exist_ok=True)
            shutil.copyfile(cobj, obj)
            hits += 1
        else:
            todo.setdefault((mode, ver), []).append((src, obj, key))

    compiled = failed = 0
    for (mode, ver), items in todo.items():
        extra = ["-thumb"] if mode == "thumb" else []
        MWCC = ST / f"tools/mwccarm/{ver}/mwccarm.exe"
        tmp_root = None
        if CC_BACKEND == "wibo":
            tmp_root = MKDS / ".wibo_tmp"
            tmp_root.mkdir(exist_ok=True)
        for i in range(0, len(items), BATCH):
            batch = items[i:i + BATCH]
            with tempfile.TemporaryDirectory(dir=tmp_root) as td:
                tdp = pathlib.Path(td)
                for src, _obj, _k in batch:
                    shutil.copyfile(src, tdp / src.name)
                names = [s.name for s, _o, _k in batch]
                subprocess.run([*cc_cmd(MWCC, workdir=td), *CFLAGS, *extra,
                                "-c", *names],
                               capture_output=True, cwd=td, timeout=600)
                for src, obj, key in batch:
                    oo = tdp / (src.stem + ".o")
                    if oo.is_file():
                        obj.parent.mkdir(parents=True, exist_ok=True)
                        shutil.copyfile(oo, obj)
                        shutil.copyfile(oo, CACHE / f"{key}.o")
                        compiled += 1
                    else:
                        # losse compile voor de echte foutmelding
                        r = subprocess.run([*cc_cmd(MWCC), *CFLAGS, *extra, "-c",
                                            str(src.resolve()), "-o", str(obj.resolve())],
                                           capture_output=True, text=True, timeout=300)
                        if obj.is_file():
                            shutil.copyfile(obj, CACHE / f"{key}.o")
                            compiled += 1
                        else:
                            failed += 1
                            err = "\n".join(l for l in (r.stdout + r.stderr).splitlines()
                                            if l.strip() and "MWCIncludes" not in l
                                            and "fixme" not in l)[:400]
                            print(f"    !! compile-fout {src.name}: {err}")
    print(f"    {len(rows)} TU('s) ({hits} uit cache, {compiled} gecompileerd"
          f"{f', {failed} FOUT' if failed else ''})")
    sys.exit(1 if failed else 0)


if __name__ == "__main__":
    main()
