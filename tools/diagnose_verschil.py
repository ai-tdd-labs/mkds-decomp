#!/usr/bin/env python3
"""diagnose_verschil.py — het VERSCHIL-speelboek als tool (zelfherstellende oogst).

Automatiseert de diagnose-ladder die 2026-07-19/20 zes brekers isoleerde:
  1. UITGEPAKTE bins diffen (arm9 zit GECOMPRIMEERD in de ROM — rauwe
     ROM-offsets zijn misleidend; kostte ons een dwaalspoor)
  2. diff-bytes op TU-ranges mappen (matched.jsonl) -> directe boosdoeners
  3. geen TU? .L_<adres>-label-truc op de xMAP: eerste label waarvan het
     echte adres != naam-adres wijst de layout-shift-oorsprong aan
  4. BLX/BL-flip herkennen (fa<->eb op instructie-grens) -> thumb-bit-klasse
  5. boosdoeners -> quarantaine + .NOTE, exit 0 = herbouwen zinvol

  tools/diagnose_verschil.py [--apply]   (zonder --apply: alleen rapport)
"""
import argparse
import json
import pathlib
import re

MKDS = pathlib.Path(__file__).resolve().parent.parent
QUAR = MKDS / "ai/hangin_quarantine.txt"

MODULES = [
    ("arm9", MKDS / "extract/eur/arm9/arm9.bin", MKDS / "build/eur/build/arm9.bin", 0x02000000),
    ("itcm", MKDS / "extract/eur/arm9/itcm.bin", MKDS / "build/eur/build/itcm.bin", 0x01FF8000),
]


def tu_map():
    out = []
    for l in (MKDS / "ai/matched.jsonl").read_text().splitlines():
        if not l.strip():
            continue
        r = json.loads(l)
        try:
            a, s = int(r["addr"], 16), int(r["size"], 16)
        except (KeyError, ValueError):
            continue
        out.append((a, a + s, r["func"]))
    out.sort()
    return out


def label_shift():
    """xMAP-truc: eerste .L_<addr>-label dat niet op z'n naam-adres ligt."""
    xmap = MKDS / "build/eur/arm9.o.xMAP"
    if not xmap.is_file():
        return None
    pat = re.compile(r"^\s+([0-9A-F]{8}) [0-9A-F]{8} \.text\s+\.L_([0-9a-f]{8})\t\((.+?)\)")
    for line in open(xmap, errors="replace"):
        m = pat.match(line)
        if m:
            actual, want = int(m.group(1), 16), int(m.group(2), 16)
            if actual != want:
                return want, actual - want, m.group(3)
    return None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--apply", action="store_true")
    args = ap.parse_args()
    tus = tu_map()
    schuldig = {}   # addr -> (func, reden)

    for naam, orig_p, build_p, base in MODULES:
        if not (orig_p.is_file() and build_p.is_file()):
            continue
        o, b = orig_p.read_bytes(), build_p.read_bytes()
        if len(o) != len(b):
            print(f"{naam}: LENGTE verschilt ({len(o):#x} vs {len(b):#x}) — layout-shift")
        diffs = [i for i in range(min(len(o), len(b))) if o[i] != b[i]]
        if not diffs:
            continue
        print(f"{naam}: {len(diffs)} diff-byte(s), eerste op 0x{base+diffs[0]:08x}")
        for i in diffs[:200]:
            addr = base + i
            hit = next(((a, f) for a, e, f in tus if a <= addr < e), None)
            if hit:
                a, f = hit
                schuldig.setdefault(a, (f, f"inhoud wijkt af op 0x{addr:08x}"))
            else:
                # BLX/BL-flip? (fa<->eb) = thumb-bit-klasse: vind de callee niet
                # hier maar meld de klasse; de boosdoener is de AANGEROEPEN TU
                if {o[i], b[i]} == {0xFA, 0xEB}:
                    print(f"  0x{addr:08x}: BLX<->BL-flip (thumb-bit-klasse) — "
                          f"doel-TU verliest z'n thumb-type; decodeer de call "
                          f"voor de dader (zie ROUTING.md)")
        if len(diffs) > 200 and not schuldig:
            ls = label_shift()
            if ls:
                want, delta, obj = ls
                print(f"  layout-shift: oorsprong .L_{want:08x} ({delta:+#x}) in {obj}")
                # boosdoener = TU direct vóór de oorsprong
                prev = next(((a, f) for a, e, f in reversed(tus) if e <= want), None)
                if prev:
                    a, f = prev
                    schuldig.setdefault(a, (f, f"layout-shift vanaf 0x{want:08x} ({delta:+#x})"))

    if not schuldig:
        print("geen directe boosdoener aangewezen — handmatige diagnose nodig")
        return 1
    print(f"\n{len(schuldig)} boosdoener(s):")
    for a, (f, reden) in sorted(schuldig.items()):
        print(f"  0x{a:08x} {f}: {reden}")
        if args.apply:
            with QUAR.open("a") as q:
                q.write(f"0x{a:08x}\n")
            (MKDS / f"ai/park/{f}.NOTE").write_text(
                f"PARKED (auto, diagnose_verschil): {reden}\n")
    if args.apply:
        lines = sorted(set(QUAR.read_text().split()))
        QUAR.write_text("\n".join(lines) + "\n")
        print("quarantaine bijgewerkt — herbouw nu")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
