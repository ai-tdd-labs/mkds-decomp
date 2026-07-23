#!/usr/bin/env python3
"""sdk_hangin.py — hang byte-matchende SDK-functies als echte objecten in de build.

De SDK-treffers hebben geen los C-bestand; de donor-C compileert wél byte-identiek.
Deze tool her-compileert de donor-bronnen (via sdk_import.build_jobs), snijdt per
gematchte functie een geïsoleerd object uit met tools/elfobj.emit (mét de
MKDS-confignaam als symbool), en registreert het als 'prebuilt' TU zodat hangin.py
er een delinks-blok voor maakt en build.sh het inlinkt.

Reloc-loze functies (leaf) gaan direct. Functies mét aanroepen krijgen relocaties
waarvan het doeladres uit de ORIGINELE ROM-bytes wordt gedecodeerd (de echte
bestemming) en gekoppeld aan het MKDS-symbool daar — zo linkt de call juist.

  tools/sdk_hangin.py            # scan + emit + schrijf ai/sdk_tus.json
  tools/sdk_hangin.py --leaf-only
"""
import argparse
import concurrent.futures as cf
import io
import json
import pathlib
import re
import struct
import sys

HERE = pathlib.Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import sdk_import as si
from elfobj import emit

MKDS = HERE.parent
CONFIG = MKDS / "config/eur/arm9"
EXTRACT = MKDS / "extract/eur"
OBJDIR = MKDS / "ai/sdk_objs"
sys.path.insert(0, str(MKDS.parent / "st/.venv/lib/python3.14/site-packages"))
from elftools.elf.elffile import ELFFile  # noqa: E402


def mkds_symbols():
    """addr -> (naam, module, size, mode); plus module-basis + bytes voor reloc-decode."""
    idx = {}
    modbytes = {}
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
    sym_re = re.compile(r"(\S+) kind:function\((arm|thumb)(?:,size=(0x\w+))?\) addr:(0x\w+)")
    any_re = re.compile(r"(\S+) kind:\S+ addr:(0x\w+)")
    names_by_addr = {}
    for name, symf, binf, base in mods:
        if binf.is_file():
            modbytes[name] = (base, binf.read_bytes())
        for line in symf.read_text().splitlines():
            m = sym_re.match(line)
            if m:
                a = int(m.group(4), 16)
                idx[a] = (m.group(1), name, int(m.group(3), 16) if m.group(3) else 0, m.group(2))
            ma = any_re.match(line)
            if ma:
                names_by_addr.setdefault(int(ma.group(2), 16), ma.group(1))
    return idx, modbytes, names_by_addr


def decode_target(mode, word_bytes, site_addr):
    """geef doeladres van een BL/BLX op site_addr; None als geen call-encoding."""
    if mode == "arm":
        w = struct.unpack("<I", word_bytes[:4])[0]
        cond = w >> 28
        op = (w >> 24) & 0xF
        if op == 0xB or (cond == 0xF and (w >> 25) == 0x7D):  # BL of BLX(imm)
            imm = w & 0xFFFFFF
            if imm & 0x800000:
                imm -= 0x1000000
            tgt = site_addr + 8 + imm * 4
            if cond == 0xF:  # BLX: H-bit
                tgt += ((w >> 24) & 1) * 2
            return tgt & ~1
    else:
        lo, hi = struct.unpack("<HH", word_bytes[:4])
        if (lo & 0xF800) == 0xF000 and (hi & 0xE000) == 0xE000:  # BL/BLX pair
            off = ((lo & 0x7FF) << 12) | ((hi & 0x7FF) << 1)
            if off & 0x400000:
                off -= 0x800000
            tgt = site_addr + 4 + off
            return tgt & ~1
    return None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--leaf-only", action="store_true")
    args = ap.parse_args()

    print("MKDS laden...")
    mkds = si.load_mkds()
    idx, modbytes, names_by_addr = mkds_symbols()
    already = set()
    mj = MKDS / "ai/matched.jsonl"
    for line in mj.read_text().splitlines():
        if line.strip():
            a = json.loads(line).get("addr", "?")
            if a != "?":
                already.add(int(a, 16))

    jobs = si.build_jobs()
    print(f"{len(jobs)} donor-bronnen compileren...")
    OBJDIR.mkdir(parents=True, exist_ok=True)
    for old in OBJDIR.glob("*.o"):
        old.unlink()

    tus = []
    seen = set()
    stats = {"leaf": 0, "reloc-ok": 0, "reloc-onbekend-doel": 0, "al-gematcht": 0}
    with cf.ThreadPoolExecutor(max_workers=4) as ex:
        for (src, _fl, _cwd), funcs in zip(jobs, ex.map(si.compile_funcs, jobs)):
            for fname, code, relocs in funcs:
                cands = mkds.get(len(code))
                if not cands:
                    continue
                for mname, addr, mod, mbytes in cands:
                    if addr in seen:
                        continue
                    if not si.words_match(code, mbytes, relocs):
                        continue
                    seen.add(addr)
                    if addr in already:
                        stats["al-gematcht"] += 1
                        break
                    info = idx.get(addr)
                    if not info:
                        break
                    cfg_name, module, size, cmode = info
                    thumb = cmode == "thumb"
                    base, data = modbytes[module]
                    # relocs vertalen naar MKDS-doelen via de ROM-bytes.
                    # type 2=ABS32 (pool-woord bevat doeladres), 1=PC24 / 10=THM_PC22 (BL/BLX).
                    rlist, ok = [], True
                    for roff in sorted(relocs):
                        rtype = relocs[roff]
                        site = addr + roff
                        w = data[site - base:site - base + 4]
                        if rtype == 2:  # R_ARM_ABS32: doel staat in het woord zelf
                            tgt = struct.unpack("<I", w)[0] & ~1
                            kind = "abs32"
                        else:           # call: decodeer BL/BLX uit de instructie
                            tgt = decode_target(cmode, w, site)
                            kind = "thumb_call" if thumb else "call"
                        if tgt is None or tgt not in names_by_addr:
                            ok = False
                            break
                        rlist.append((roff, names_by_addr[tgt], kind))
                    if relocs and not ok:
                        stats["reloc-onbekend-doel"] += 1
                        break
                    if relocs and args.leaf_only:
                        break
                    # thumb-functies met niet-4-uitgelijnde grootte laten alignment-
                    # padding na tot de volgende functie; die hoort bij dit blok.
                    emit_size = size or len(code)
                    aligned = (emit_size + 3) & ~3
                    if aligned != emit_size:
                        pad = data[addr - base + emit_size:addr - base + aligned]
                        code = code + pad
                        emit_size = aligned
                    obj = emit(cfg_name, code, thumb=thumb, relocs=rlist)
                    safe = re.sub(r"[^A-Za-z0-9_]", "_", cfg_name)
                    op = OBJDIR / f"{safe}.o"
                    op.write_bytes(obj)
                    tus.append({"addr": hex(addr), "func": cfg_name, "module": module,
                                "size": hex(size or len(code)), "obj": str(op.relative_to(MKDS)),
                                "donor": fname, "relocs": len(rlist)})
                    stats["reloc-ok" if relocs else "leaf"] += 1
                    break

    (MKDS / "ai/sdk_tus.json").write_text(json.dumps(tus, indent=1))
    print(f"\ngeëmit: {stats['leaf']} leaf + {stats['reloc-ok']} met-reloc = {len(tus)} SDK-TU's")
    print(f"overgeslagen: {stats['reloc-onbekend-doel']} (reloc-doel onbekend), "
          f"{stats['al-gematcht']} (al in matched.jsonl)")
    print("-> ai/sdk_tus.json; draai tools/hangin.py --generate --build")


if __name__ == "__main__":
    main()
