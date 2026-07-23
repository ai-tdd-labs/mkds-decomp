#!/usr/bin/env python3
"""elfobj.py — emit een minimaal ARM ELF-REL-object met één functie.

Voor SDK-inhang: de donor-C compileert byte-identiek, maar we willen per functie
een geïsoleerd, linkbaar object (niet het hele donor-object met tientallen andere
functies). Deze emitter bouwt precies de structuur die mwccarm/mwldarm verwacht:
NULL / .text(PROGBITS,AX) / .symtab / .strtab / .shstrtab, met een $a- of
$t-mapping-symbool (LOCAL, STT_FUNC, offset 0) en het functiesymbool (GLOBAL).

Optioneel relocaties: lijst van (offset, symboolnaam, type) met type R_ARM_ABS32(2)
/ R_ARM_PC24(1) / R_ARM_THM_PC22(10); de addend zit al in de code (REL, zoals mwcc).
"""
import struct

R_ARM = {"abs32": 2, "pc24": 1, "thm_pc22": 10, "call": 1, "thumb_call": 10}


def emit(func_name, code, thumb=False, relocs=()):
    """geeft de bytes van een .o terug. relocs = [(offset, sym, kind)]."""
    ext_syms = []
    seen = {}
    for _off, sym, _k in relocs:
        if sym not in seen:
            seen[sym] = len(ext_syms)
            ext_syms.append(sym)

    # ---- .strtab: namen van symbolen ----
    mapname = b"$t" if thumb else b"$a"
    strtab = b"\x00"
    def add_str(s):
        nonlocal strtab
        off = len(strtab)
        strtab += s + b"\x00"
        return off
    off_map = add_str(mapname)
    off_func = add_str(func_name.encode())
    off_ext = {s: add_str(s.encode()) for s in ext_syms}

    # ---- .symtab: null, $a/$t(local), func(global), [externals(global,undef)] ----
    STB_LOCAL, STB_GLOBAL = 0, 1
    STT_NOTYPE, STT_FUNC = 0, 2
    def sym(name_off, value, size, info, shndx):
        return struct.pack("<IIIBBH", name_off, value, size, info, 0, shndx)
    symtab = sym(0, 0, 0, 0, 0)                                    # 0: null
    symtab += sym(off_map, 0, 0, (STB_LOCAL << 4) | STT_FUNC, 1)   # 1: $a/$t -> .text (idx1)
    local_count = 2                                                # null + mapping
    func_sym_index = 2
    symtab += sym(off_func, 0, len(code), (STB_GLOBAL << 4) | STT_FUNC, 1)  # 2: func
    ext_index = {}
    for i, s in enumerate(ext_syms):
        ext_index[s] = func_sym_index + 1 + i
        symtab += sym(off_ext[s], 0, 0, (STB_GLOBAL << 4) | STT_NOTYPE, 0)  # undef

    # ---- .rel.text ----
    rel = b""
    for off, s, kind in relocs:
        r_info = (ext_index[s] << 8) | R_ARM[kind]
        rel += struct.pack("<II", off, r_info)

    # ---- secties samenstellen ----
    # layout: [0]NULL [1].text [2].symtab [3].strtab [4].shstrtab [5?].rel.text
    have_rel = bool(rel)
    shstr = b"\x00"
    names = {}
    for nm in (b".text", b".symtab", b".strtab", b".shstrtab", b".rel.text"):
        names[nm] = len(shstr); shstr += nm + b"\x00"

    # data-blokken achter elkaar; bereken offsets
    ehsize = 52
    # secties in vaste volgorde
    sec = []  # (name, type, flags, link, info, addralign, entsize, data)
    sec.append((b"", 0, 0, 0, 0, 0, 0, b""))                                    # 0 NULL
    sec.append((b".text", 1, 0x6, 0, 0, 4, 0, code))                            # 1 PROGBITS AX
    symtab_idx = 2
    strtab_idx = 3
    sec.append((b".symtab", 2, 0, strtab_idx, local_count, 4, 16, symtab))      # 2 SYMTAB (link->strtab, info=local_count)
    sec.append((b".strtab", 3, 0, 0, 0, 1, 0, strtab))                          # 3 STRTAB
    sec.append((b".shstrtab", 3, 0, 0, 0, 1, 0, shstr))                         # 4 STRTAB
    if have_rel:
        sec.append((b".rel.text", 9, 0, symtab_idx, 1, 4, 8, rel))             # 5 REL (link->symtab, info->.text idx1)

    # plaats sectie-data na de ELF-header, 4-uitgelijnd
    offsets = []
    cur = ehsize
    for nm, t, fl, lk, inf, al, es, data in sec:
        if t == 0:
            offsets.append(0); continue
        cur = (cur + 3) & ~3
        offsets.append(cur)
        cur += len(data)
    cur = (cur + 3) & ~3
    shoff = cur

    out = bytearray()
    # ELF-header
    e_ident = b"\x7fELF\x01\x01\x01\x00" + b"\x00" * 8
    out += e_ident
    out += struct.pack("<HHIIIIIHHHHHH",
                       1, 40, 1, 0, 0, shoff, 0x2100000,
                       52, 0, 0, 40, len(sec), 4)  # e_type,mach,ver,entry,phoff,shoff,flags,ehsize,phentsize,phnum,shentsize,shnum,shstrndx=4
    # sectie-data
    for (nm, t, fl, lk, inf, al, es, data), o in zip(sec, offsets):
        if t == 0:
            continue
        while len(out) < o:
            out += b"\x00"
        out += data
    while len(out) < shoff:
        out += b"\x00"
    # sectie-headers
    for (nm, t, fl, lk, inf, al, es, data), o in zip(sec, offsets):
        name_off = shstr.index(nm + b"\x00") if nm else 0
        out += struct.pack("<IIIIIIIIII",
                           name_off, t, fl, 0, o, len(data), lk, inf, al, es)
    return bytes(out)


if __name__ == "__main__":
    # zelftest: emit Os_Thread_GetPriority en toon .text
    import io, sys
    sys.path.insert(0, "../st/.venv/lib/python3.14/site-packages")
    from elftools.elf.elffile import ELFFile
    code = bytes.fromhex("700090e51eff2fe1")
    obj = emit("Os_Thread_GetPriority", code, thumb=False)
    elf = ELFFile(io.BytesIO(obj))
    print("secties:", [s.name for s in elf.iter_sections()])
    st = elf.get_section_by_name(".symtab")
    print("symbolen:", [(s.name, s['st_info']['bind'], s['st_shndx']) for s in st.iter_symbols()])
    print(".text:", elf.get_section_by_name(".text").data().hex())
