#!/usr/bin/env python3
"""fix_padding.py — corrigeer gemengde sectie-padding in de herbouwde ROM.

Nintendo's originele build padt niet uniform: 0x00 na het arm9-blok, de
overlay-tabel en tussen overlay-bestanden; 0xff na arm7/FNT/FAT en in het
file-image. ds-rom kent maar één section_padding_value en kan dat niet
uitdrukken. Deze tool berekent de GAP-regio's (bytes die niet door header,
programma's, tabellen of bestanden gedekt worden) uit de HERBOUWDE ROM zelf en
stempelt daar de paddingbytes van het origineel. Veiligheid: een gap wordt
alleen gekopieerd als de originele bytes er uniform 0x00 of 0xff zijn — anders
abort (dan is het geen padding maar gemiste content).

  tools/fix_padding.py <gebouwde.nds> <origineel.nds>
"""
import struct
import sys


def covered_ranges(d):
    def rd(off):
        return struct.unpack_from("<I", d, off)[0]
    covered = [(0, 0x4000)]  # header + secure-gebied start; arm9 begint op arm9_off
    arm9_off, arm9_sz = rd(0x20), rd(0x2c)
    covered.append((arm9_off, arm9_off + arm9_sz + 12))  # + arm9-footer
    arm7_off, arm7_sz = rd(0x30), rd(0x3c)
    covered.append((arm7_off, arm7_off + arm7_sz))
    fnt_off, fnt_sz = rd(0x40), rd(0x44)
    covered.append((fnt_off, fnt_off + fnt_sz))
    fat_off, fat_sz = rd(0x48), rd(0x4c)
    covered.append((fat_off, fat_off + fat_sz))
    ov9_off, ov9_sz = rd(0x50), rd(0x54)
    covered.append((ov9_off, ov9_off + ov9_sz))
    ov7_off, ov7_sz = rd(0x58), rd(0x5c)
    covered.append((ov7_off, ov7_off + ov7_sz))
    banner_off = rd(0x68)
    if banner_off:
        covered.append((banner_off, banner_off + 0x840))
    rom_size = rd(0x80)
    covered.append((rom_size, rom_size + 136))  # multiboot-signature
    for i in range(0, fat_sz, 8):
        s, e = struct.unpack_from("<II", d, fat_off + i)
        covered.append((s, e))
    return sorted(r for r in covered if r[1] > r[0])


def main():
    built_p, orig_p = sys.argv[1], sys.argv[2]
    b = bytearray(open(built_p, "rb").read())
    o = open(orig_p, "rb").read()
    if len(b) != len(o):
        print(f"! lengteverschil ({len(b)} vs {len(o)}), padding-fix niet toepasbaar")
        sys.exit(1)

    cov = covered_ranges(b)
    merged = []
    for s, e in cov:
        if merged and s <= merged[-1][1]:
            merged[-1][1] = max(merged[-1][1], e)
        else:
            merged.append([s, e])

    patched = 0
    gaps = []
    prev = 0
    for s, e in merged + [[len(b), len(b)]]:
        if s > prev:
            gaps.append((prev, s))
        prev = max(prev, e)
    for s, e in gaps:
        seg = o[s:e]
        vals = set(seg)
        if not vals <= {0x00, 0xff}:
            print(f"! gap 0x{s:x}..0x{e:x} in origineel niet uniform pad "
                  f"(waarden {sorted(hex(v) for v in list(vals)[:5])}) — overslaan")
            continue
        if b[s:e] != seg:
            b[s:e] = seg
            patched += e - s
    if patched:
        open(built_p, "wb").write(bytes(b))
    print(f"padding: {len(gaps)} gaps, {patched} bytes gestempeld")


if __name__ == "__main__":
    main()
