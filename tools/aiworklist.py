#!/usr/bin/env python3
"""aiworklist.py - find unmatched functions and build annotated context rows.

List unmatched functions (not covered by any delinked source file range):
  tools/aiworklist.py list [--module arm9|ovNNN] [--min 0x20] [--max 0x100] [--limit 30]

Emit a full context row for one function (annotated disasm, callees, pool, hex):
  tools/aiworklist.py row FUNC_NAME [--module ovNNN]
"""

import argparse
import pathlib
import re
import struct
import sys

from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB

ROOT = pathlib.Path(__file__).resolve().parent.parent
VERSION = "eur"
CONFIG = ROOT / "config" / VERSION / "arm9"
EXTRACT = ROOT / "extract" / VERSION

SYM_RE = re.compile(
    r"^(?P<name>\S+)\s+kind:function\((?P<mode>arm|thumb)(?:,size=(?P<size>0x[0-9a-fA-F]+))?\)"
    r"\s+addr:(?P<addr>0x[0-9a-fA-F]+)")
ANY_SYM_RE = re.compile(r"^(?P<name>\S+)\s+kind:\S+\s+addr:(?P<addr>0x[0-9a-fA-F]+)")
RELOC_RE = re.compile(r"^from:(0x[0-9a-fA-F]+)\s+kind:(\S+)\s+to:(0x[0-9a-fA-F]+)")


def modules():
    yield "arm9", CONFIG
    ovdir = CONFIG / "overlays"
    if ovdir.is_dir():
        for ov in sorted(ovdir.iterdir()):
            if (ov / "symbols.txt").is_file():
                yield ov.name, ov


def parse_functions(cfg: pathlib.Path):
    out = []
    for line in (cfg / "symbols.txt").read_text().splitlines():
        m = SYM_RE.match(line)
        if m:
            out.append((m.group("name"), m.group("mode"),
                        int(m.group("addr"), 16),
                        int(m.group("size"), 16) if m.group("size") else 0))
    return out


def parse_all_symbols(cfg: pathlib.Path):
    """addr -> name for every symbol (functions + data) in a module config."""
    out = {}
    for line in (cfg / "symbols.txt").read_text().splitlines():
        m = ANY_SYM_RE.match(line)
        if m:
            out[int(m.group("addr"), 16)] = m.group("name")
    return out


def parse_matched_ranges(cfg: pathlib.Path):
    """Ranges of .text already attributed to a source file in delinks.txt."""
    ranges = []
    cur_file = None
    for line in (cfg / "delinks.txt").read_text().splitlines():
        if line and not line.startswith((" ", "\t")) and line.rstrip().endswith(":"):
            cur_file = line.rstrip()[:-1]
        elif cur_file and ".text" in line:
            m = re.search(r"start:(0x[0-9a-fA-F]+)\s+end:(0x[0-9a-fA-F]+)", line)
            if m:
                ranges.append((int(m.group(1), 16), int(m.group(2), 16)))
    return ranges


def parse_relocs(cfg: pathlib.Path):
    out = {}
    relocfile = cfg / "relocs.txt"
    if relocfile.is_file():
        for line in relocfile.read_text().splitlines():
            m = RELOC_RE.match(line)
            if m:
                out[int(m.group(1), 16)] = (m.group(2), int(m.group(3), 16))
    return out


def module_binary(module: str, cfg: pathlib.Path):
    if module == "arm9":
        return EXTRACT / "arm9" / "arm9.bin", 0x02000000
    binpath = EXTRACT / "arm9_overlays" / f"{module}.bin"
    for line in (cfg / "delinks.txt").read_text().splitlines():
        m = re.search(r"start:(0x[0-9a-fA-F]+)", line)
        if m:
            return binpath, int(m.group(1), 16)
    raise SystemExit(f"no base for {module}")


def unmatched(cfg: pathlib.Path):
    ranges = parse_matched_ranges(cfg)
    for name, mode, addr, size in parse_functions(cfg):
        if not any(s <= addr < e for s, e in ranges):
            yield name, mode, addr, size


def cmd_list(args):
    rows = []
    for mod, cfg in modules():
        if args.module and mod != args.module:
            continue
        for name, mode, addr, size in unmatched(cfg):
            if size < args.min or (args.max and size > args.max):
                continue
            rows.append((size, mod, name, mode, addr))
    rows.sort()
    total = len(rows)
    for size, mod, name, mode, addr in rows[:args.limit]:
        print(f"{mod:6} {mode:5} 0x{addr:08x} size=0x{size:<5x} {name}")
    print(f"-- {total} unmatched functions in band (showing {min(args.limit, total)})")


def cmd_row(args):
    for mod, cfg in modules():
        if args.module and mod != args.module:
            continue
        hit = next(((n, m, a, s) for n, m, a, s in parse_functions(cfg)
                    if n == args.name), None)
        if hit:
            break
    else:
        sys.exit(f"{args.name} not found")
    name, mode, addr, size = hit

    binpath, base = module_binary(mod, cfg)
    data = binpath.read_bytes()
    code = data[addr - base: addr - base + size]

    # name maps: this module + arm9 (overlays call into main freely)
    names = parse_all_symbols(CONFIG)
    if cfg != CONFIG:
        names.update(parse_all_symbols(cfg))
    relocs = parse_relocs(cfg)

    md = Cs(CS_ARCH_ARM, CS_MODE_THUMB if mode == "thumb" else CS_MODE_ARM)
    md.detail = False

    print(f"function {name}")
    print(f"module {mod}  mode {mode}  addr 0x{addr:08x}  size 0x{size:x}")
    print(f"target_hex {code.hex()}")
    print("disasm:")
    callees = set()
    lines = list(md.disasm(code, addr))
    covered = lines[-1].address + lines[-1].size - addr if lines else 0
    for ins in lines:
        note = ""
        if ins.mnemonic.startswith(("bl", "blx", "b")) and ins.op_str.startswith("#"):
            tgt = int(ins.op_str.lstrip("#"), 0)
            if tgt in names and not (addr <= tgt < addr + size):
                note = f" ; -> {names[tgt]}"
                if ins.mnemonic.startswith("bl"):
                    callees.add(names[tgt])
        elif ins.address in relocs:
            kind, tgt = relocs[ins.address]
            note = f" ; reloc {kind} -> {names.get(tgt, hex(tgt))}"
        m = re.search(r"\[pc, #(0x[0-9a-fA-F]+|\d+)\]", ins.op_str)
        if m:
            imm = int(m.group(1), 0)
            pc = (ins.address + 4) & ~3 if mode == "thumb" else ins.address + 8
            pool = pc + imm
            if pool - addr + 4 <= size:
                val = struct.unpack_from("<I", code, pool - addr)[0]
                if pool in relocs:
                    _, tgt = relocs[pool]
                    note += f" ; pool -> &{names.get(tgt, hex(tgt))}"
                elif val in names:
                    note += f" ; pool -> &{names[val]} (0x{val:08x})"
                else:
                    note += f" ; pool = 0x{val:08x}"
        print(f"  0x{ins.address:08x}: {ins.mnemonic:8} {ins.op_str}{note}")
    if covered < size:
        pooldata = code[covered:]
        print(f"trailing pool/data ({size - covered} bytes):")
        for off in range(0, len(pooldata) & ~3, 4):
            val = struct.unpack_from("<I", pooldata, off)[0]
            paddr = addr + covered + off
            note = ""
            if paddr in relocs:
                _, tgt = relocs[paddr]
                note = f"  ; &{names.get(tgt, hex(tgt))}"
            elif val in names:
                note = f"  ; &{names[val]}?"
            print(f"  0x{paddr:08x}: 0x{val:08x}{note}")
    if callees:
        print("callees:")
        for c in sorted(callees):
            print(f"  {c}")


def main():
    ap = argparse.ArgumentParser()
    sub = ap.add_subparsers(dest="cmd", required=True)
    lp = sub.add_parser("list")
    lp.add_argument("--module")
    lp.add_argument("--min", type=lambda x: int(x, 0), default=0)
    lp.add_argument("--max", type=lambda x: int(x, 0), default=0)
    lp.add_argument("--limit", type=int, default=40)
    lp.set_defaults(func=cmd_list)
    rp = sub.add_parser("row")
    rp.add_argument("name")
    rp.add_argument("--module")
    rp.set_defaults(func=cmd_row)
    args = ap.parse_args()
    args.func(args)


if __name__ == "__main__":
    main()
