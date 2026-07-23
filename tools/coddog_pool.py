#!/usr/bin/env python3
"""coddog_pool.py — familie-clone voor functies die alleen in pool-constanten verschillen.

De hoogste-opbrengst coddog-vorm: een reeks functies met identiek instructie-skelet
die alleen verschillen in de geladen pool-woorden (meestal data-adressen). Eén al
gematchte functie is het sjabloon; deze tool vindt de siblings, substitueert per
sibling de pool-adressen in de C, verifieert byte-match via het orakel en registreert.

Werking: neem het sjabloon (addr + scratch-C). Elk 4-byte pool-woord in het sjabloon
dat als `data_<hex>`/`func_<hex>`/`0x<hex>` in de C voorkomt is een 'gat'. Voor elke
ongematchte functie van dezelfde grootte waarvan de NIET-pool-bytes identiek zijn,
lees de eigen pool-woorden, vul ze in het C-sjabloon en verifieer.

  tools/coddog_pool.py --template 0x020db268 [--limit 10] [--size 0x50]
"""
import argparse
import json
import pathlib
import re
import struct
import subprocess
import sys
import time

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent.parent.parent / "st/.venv/lib/python3.14/site-packages"))
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM  # noqa: E402

MKDS = pathlib.Path(__file__).resolve().parent.parent
CONFIG = MKDS / "config/eur/arm9"
EXTRACT = MKDS / "extract/eur"
PY = str(MKDS.parent / "st/.venv/bin/python")
MD = Cs(CS_ARCH_ARM, CS_MODE_ARM)
SYM_RE = re.compile(r"(\S+) kind:function\((arm|thumb)(?:,size=(0x\w+))?\) addr:(0x\w+)")


def load_syms():
    out = {}
    for line in (CONFIG / "symbols.txt").read_text().splitlines():
        m = SYM_RE.match(line)
        if m and m.group(3):
            out[int(m.group(4), 16)] = (m.group(1), int(m.group(3), 16))
    return out


def func_modes():
    """addr -> 'arm'/'thumb' voor elke config-functie (voor interworking-check)."""
    out = {}
    for line in (CONFIG / "symbols.txt").read_text().splitlines():
        m = SYM_RE.match(line)
        if m:
            out[int(m.group(4), 16)] = m.group(2)
    return out


def name_by_addr():
    """addr -> config-naam over ALLE kinds (functie, data, bss, label)."""
    out = {}
    any_re = re.compile(r"(\S+) kind:\S+ addr:(0x\w+)")
    for line in (CONFIG / "symbols.txt").read_text().splitlines():
        m = any_re.match(line)
        if m:
            out.setdefault(int(m.group(2), 16), m.group(1))
    return out


def matched_addrs():
    a = set()
    for line in (MKDS / "ai/matched.jsonl").read_text().splitlines():
        if line.strip():
            x = json.loads(line).get("addr", "?")
            if x != "?":
                a.add(int(x, 16))
    for hf in MKDS.glob("ai/sdk_import_hits*.json"):
        for r in json.loads(hf.read_text()):
            a.add(int(r["addr"], 16))
    return a


def pool_offsets(code, size):
    """offsets van 4-byte woorden die géén ARM-instructie zijn (pool-constanten)."""
    ins_end = {}
    for i in MD.disasm(code, 0):
        ins_end[i.address] = True
    # alles wat capstone niet als instructie op een 4-grens ziet = pool
    return [off for off in range(0, size, 4) if off not in ins_end]


def find_template_c(addr):
    for r in (json.loads(l) for l in (MKDS / "ai/matched.jsonl").read_text().splitlines() if l.strip()):
        if r.get("addr", "?") != "?" and int(r["addr"], 16) == addr:
            return MKDS / "ai/scratch" / r["scratch"]
    return None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--template", type=lambda x: int(x, 16), required=True)
    ap.add_argument("--size", type=lambda x: int(x, 16))
    ap.add_argument("--limit", type=int, default=10)
    ap.add_argument("--dry", action="store_true")
    args = ap.parse_args()

    syms = load_syms()
    done = matched_addrs()
    data = (EXTRACT / "arm9/arm9.bin").read_bytes()
    base = 0x02000000

    tname, tsize = syms[args.template]
    size = args.size or tsize
    tcode = data[args.template - base:args.template - base + size]
    tc_path = find_template_c(args.template)
    if not tc_path:
        print(f"! geen scratch-C voor sjabloon {tname}"); sys.exit(1)
    tc = tc_path.read_text()

    names = name_by_addr()
    # pool-slot = 4-byte woord dat naar een config-symbool wijst waarvan de NAAM in de
    # C staat (data_XXXX, of een functienaam bij een indirecte thunk-call via pool),
    # OF waarvan de rauwe hex in de C staat. Per slot bewaren we hoe het in de C heet.
    tvals = {}   # offset -> (sjabloon-waarde, tekst-in-C)
    for off in range(0, size, 4):
        v = struct.unpack_from("<I", tcode, off)[0]
        token = None
        for cand in (names.get(v), names.get(v & ~1)):
            if cand and cand in tc:
                token = cand
                break
        if token is None and (f"{v:08x}" in tc or f"{v:x}" in tc):
            token = f"{v:08x}" if f"{v:08x}" in tc else f"{v:x}"
        if token:
            tvals[off] = (v, token)

    # call-slot = relatieve bl/blx-instructie waarvan het doel een config-functie is
    # waarvan de NAAM in de C staat. Per sibling verschilt het doel; we maskeren de
    # instructie-bytes en substitueren de doelnaam.
    cslots = {}  # offset -> doel-config-naam
    for i in MD.disasm(tcode, args.template):
        off = i.address - args.template
        if i.mnemonic in ("bl", "blx") and i.op_str.startswith("#"):
            tgt = int(i.op_str[1:], 16) & ~1
            nm = names.get(tgt) or names.get(tgt | 1)
            if nm and nm in tc:
                cslots[off] = nm
    print(f"sjabloon {tname} @0x{args.template:08x} size=0x{size:x}: "
          f"{len(tvals)} pool-slot(s) + {len(cslots)} call-slot(s) "
          f"({', '.join([t for _, t in tvals.values()] + list(cslots.values()))})")

    # skelet-masker: bytes buiten pool- en call-slots moeten identiek zijn
    def nonpool_equal(code):
        for off in range(0, size, 4):
            if off in tvals or off in cslots:
                continue
            if code[off:off + 4] != tcode[off:off + 4]:
                return False
        return True

    def sib_call_target(addr, off):
        w = struct.unpack_from("<I", data, addr - base + off)[0]
        imm = w & 0xFFFFFF
        if imm & 0x800000:
            imm -= 0x1000000
        h = (w >> 24) & 1 if (w >> 28) == 0xF else 0  # BLX H-bit
        return ((addr + off) + 8 + imm * 4 + h * 2) & ~1

    def render(addr):
        c = tc
        for off, (tval, token) in tvals.items():
            sval = struct.unpack_from("<I", data, addr - base + off)[0]
            repl = names.get(sval) or names.get(sval & ~1)
            if repl is None:
                repl = f"{sval:08x}" if len(token) == 8 and all(ch in "0123456789abcdef" for ch in token) else f"{sval:x}"
            c = c.replace(token, repl)
        for off, token in cslots.items():
            tgt = sib_call_target(addr, off)
            repl = names.get(tgt) or names.get(tgt | 1)
            if repl:
                c = c.replace(token, repl)
        # de gedefinieerde functie krijgt de CONFIG-naam op dat adres (niet func_<addr>);
        # anders verwijzen andere TU's die 'm aanroepen naar de config-naam terwijl deze
        # TU 'm onder func_<addr> definieert -> undefined bij de link.
        return c.replace(tname, names.get(addr) or f"func_{addr:08x}")

    modes = func_modes()
    # sjabloon-call-doelmodes: per call-slot arm/thumb van het doel
    tmpl_modes = {off: modes.get(sib_call_target(args.template, off)) for off in cslots}
    dropped_mode = 0

    def interwork_ok(addr):
        """siblings' call-doelmodes moeten matchen met het sjabloon; anders veneer/blx-
        verschil dat het orakel niet ziet maar de link wel (layout-shift)."""
        for off in cslots:
            if modes.get(sib_call_target(addr, off)) != tmpl_modes[off]:
                return False
        return True

    cands = []
    for addr, (nm, sz) in sorted(syms.items()):
        if sz != size or addr in done or addr == args.template:
            continue
        off = addr - base
        if not (0 <= off and off + size <= len(data)):
            continue
        if not nonpool_equal(data[off:off + size]):
            continue
        if not interwork_ok(addr):
            dropped_mode += 1
            continue
        cands.append((addr, nm))
    if dropped_mode:
        print(f"  ({dropped_mode} siblings overgeslagen: arm/thumb-call-mode wijkt af van sjabloon)")
    def sib_name(addr):
        return names.get(addr) or f"func_{addr:08x}"

    print(f"{len(cands)} ongematchte siblings met identiek skelet\n")

    matched, t0 = [], time.time()
    for addr, nm in cands[:args.limit]:
        ts = time.time()
        fname = sib_name(addr)
        src = MKDS / f"ai/scratch/cdp_{addr:08x}.c"
        src.write_text(render(addr))
        r = subprocess.run([PY, "tools/aimatch.py", "--src", str(src), "--func",
                            fname, "--module", "arm9", "--addr", hex(addr),
                            "--size", hex(size), "--quiet"],
                           capture_output=True, text=True, cwd=MKDS, timeout=120)
        ok = "match=True" in r.stdout
        dt = time.time() - ts
        print(f"  {'OK ' if ok else 'MIS'} {fname}  {dt:.1f}s")
        if ok:
            matched.append((addr, fname, src.name))
    tot = time.time() - t0
    print(f"\n{len(matched)}/{min(len(cands), args.limit)} gematcht in {tot:.1f}s "
          f"({tot / max(min(len(cands), args.limit), 1):.1f}s/functie)")

    if matched and not args.dry:
        with (MKDS / "ai/matched.jsonl").open("a") as f:
            for addr, fname, scr in matched:
                f.write(json.dumps({"func": fname, "naam": fname,
                                    "module": "arm9", "addr": hex(addr), "size": hex(size),
                                    "bron": f"coddog-pool({tname})", "scratch": scr}) + "\n")
        print(f"{len(matched)} toegevoegd aan matched.jsonl")
        # naamgeving loopt meteen mee: werk het grootboek bij met de bewijs-check
        # (voorstellen + bewijs voor de nieuwe functies; geen code-wijziging).
        try:
            import names as _names
            _n, ledger, _r, _a = _names.compute()
            _names.write_ledger(ledger)
            print("  naam-grootboek bijgewerkt (ai/names.jsonl)")
        except Exception as e:
            print(f"  (naamgeving overgeslagen: {e})")


if __name__ == "__main__":
    main()
