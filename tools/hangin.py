#!/usr/bin/env python3
"""hangin.py — hang gematchte functies als echte TU's in de build (sm64ds-stijl).

Neemt elke bevestigde match uit ai/matched.jsonl, kopieert de scratch-C naar
src/<module>/<func>.c, schrijft een 'complete' file-blok in de juiste delinks.txt
en een regel in ai/tus.txt (bron->objectpad). build.sh compileert die TU's ná de
delink en linkt ze mee; de SHA1-poort vergelijkt met de originele ROM.

Niet elke byte-match linkt ook goed: een reloc kan naar het verkeerde symbool
wijzen (WRONG-DEST) -> juiste bytes, verkeerde bestemming -> SHA1 breekt. Daarom:
  --generate   schrijf src/ + delinks-blokken + tus.txt voor alle kandidaten
  --build      draai build.sh, rapporteer SHA1
  --bisect     bij SHA1-mismatch: binair zoeken welke TU's breken, zet ze in
               ai/hangin_quarantine.txt en herbouw tot de ROM weer matcht

  tools/hangin.py --generate --build --bisect
"""
import argparse
import json
import pathlib
import re
import shutil
import subprocess
import sys

MKDS = pathlib.Path(__file__).resolve().parent.parent
CONFIG = MKDS / "config/eur/arm9"
SRC = MKDS / "src"
QUAR = MKDS / "ai/hangin_quarantine.txt"
TUS = MKDS / "ai/tus.txt"
SECTION_HDR_RE = re.compile(r"^\s+\.\w+\s+start:0x")


def module_dir(mod):
    if mod == "arm9":
        return CONFIG
    if mod in ("itcm", "dtcm"):
        return CONFIG / mod
    return CONFIG / "overlays" / mod


def load_candidates():
    """bruikbare matches: scratch bestaat, addr+size bekend."""
    out = []
    for line in (MKDS / "ai/matched.jsonl").read_text().splitlines():
        if not line.strip():
            continue
        r = json.loads(line)
        scratch = r.get("scratch")
        if not scratch or r.get("addr", "?") == "?" or r.get("size", "?") == "?":
            continue
        sp = MKDS / "ai/scratch" / scratch
        if not sp.is_file():
            continue
        out.append({
            "func": r["func"], "module": r.get("module", "arm9"),
            "addr": int(r["addr"], 16), "size": int(r["size"], 16),
            "scratch": sp, "cpp": scratch.endswith(".cpp"), "mwcc": r.get("mwcc", ""),
        })
    # prebuilt SDK-TU's meenemen (geëmit door sdk_hangin.py) zodat de bisect ze
    # ook kan quarantainen als een reloc verkeerd blijkt
    sf = MKDS / "ai/sdk_tus.json"
    if sf.is_file():
        for r in json.loads(sf.read_text()):
            out.append({"func": r["func"], "module": r["module"],
                        "addr": int(r["addr"], 16), "size": int(r["size"], 16),
                        "obj": r["obj"], "prebuilt": True})
    # dedup op adres, sorteer
    seen, uniq = set(), []
    for c in sorted(out, key=lambda x: (x["module"], x["addr"])):
        if c["addr"] in seen:
            continue
        seen.add(c["addr"])
        uniq.append(c)
    return uniq


def read_quarantine():
    if QUAR.is_file():
        return {int(x, 16) for x in QUAR.read_text().split() if x.strip()}
    return set()


def base_delinks(mod_dir):
    """alleen het bovenste sectie-header-blok (stopt bij eerste TU-blok/lege regel).

    LET OP: TU-blokken bevatten óók '.text start:0x..'-regels, dus filteren op de
    regex zou die meenemen. De module-layout is het eerste aaneengesloten blok
    met 'kind:'-attributen; daar stoppen we."""
    hdr = []
    for l in (mod_dir / "delinks.txt").read_text().splitlines():
        if SECTION_HDR_RE.match(l) and "kind:" in l:
            hdr.append(l)
        else:
            break
    return hdr


SYM_LINE_RE = re.compile(r"^(\S+)( kind:function\([^)]*\) addr:(0x\w+))")


def sync_symbol_names(active):
    """zorg dat het config-symbool op elk TU-adres exact de TU-naam draagt.

    In sm64ds/st is bestandsnaam == config-symbool. Als onze gedecompileerde naam
    (bv. memchr) afwijkt van het config-symbool (func_02134db0), verwijst het
    gap-object naar de config-naam terwijl onze TU de andere levert -> breuk.
    relocs verwijzen op ADRES, dus hernoemen in symbols.txt is veilig."""
    want = {}  # (module, addr) -> naam
    for c in active:
        want[(c["module"], c["addr"])] = c["func"]
    changed = 0
    mods = {c["module"] for c in active}
    for mod in mods:
        sf = module_dir(mod) / "symbols.txt"
        lines = sf.read_text().splitlines()
        out = []
        for line in lines:
            m = SYM_LINE_RE.match(line)
            if m:
                addr = int(m.group(3), 16)
                naam = want.get((mod, addr))
                oud = m.group(1)
                # GUARD: nooit een betekenisvolle config-naam (bv. LoadBankEgg1MapObject,
                # die door andere TU's als callback wordt aangeroepen) overschrijven met
                # een generieke func_<addr>/data_<addr> -> dat orphant die verwijzingen.
                generic = re.compile(r"^(func|data|lbl)_0[12][0-9a-f]{6}$")
                if naam and naam != oud and not (generic.match(naam) and not generic.match(oud)):
                    line = naam + m.group(2)
                    changed += 1
            out.append(line)
        sf.write_text("\n".join(out) + "\n")
    return changed


def load_sdk_tus(quar):
    """prebuilt SDK-objecten uit ai/sdk_tus.json (geëmit door sdk_hangin.py)."""
    f = MKDS / "ai/sdk_tus.json"
    if not f.is_file():
        return []
    out = []
    for r in json.loads(f.read_text()):
        addr = int(r["addr"], 16)
        if addr in quar:
            continue
        out.append({"func": r["func"], "module": r["module"], "addr": addr,
                    "size": int(r["size"], 16), "obj": r["obj"], "prebuilt": True})
    return out


def mode_of(c):
    """arm/thumb van dit TU-adres volgens de config-symbols."""
    md = module_dir(c["module"]) / "symbols.txt"
    pat = re.compile(rf"kind:function\((arm|thumb)[^)]*\) addr:0x0*{c['addr']:x}\b", re.I)
    for line in md.read_text().splitlines():
        m = pat.search(line)
        if m:
            return m.group(1)
    return "arm"


def generate(cands, quar):
    active = [c for c in cands if c["addr"] not in quar]
    active.sort(key=lambda x: (x["module"], x["addr"]))
    sync_symbol_names(active)
    # groepeer per module
    by_mod = {}
    for c in active:
        by_mod.setdefault(c["module"], []).append(c)

    tus = []        # bron<TAB>obj  (te compileren C)
    prebuilt = []   # geëmit-obj<TAB>delink-doelpad  (te kopiëren)
    # ruim oude src/ hangin-map
    if SRC.is_dir():
        shutil.rmtree(SRC)
    # ALLE module-delinks eerst terug naar kale headers (anders blijven stale
    # TU-blokken staan in modules waarvan alle TU's nu geparkeerd zijn)
    all_mods = ["arm9", "itcm", "dtcm"] + [ov.name for ov in (CONFIG / "overlays").glob("ov*")]
    for mod in all_mods:
        md = module_dir(mod)
        if (md / "delinks.txt").is_file():
            (md / "delinks.txt").write_text("\n".join(base_delinks(md)) + "\n")
    for mod, cs in by_mod.items():
        md = module_dir(mod)
        hdr = base_delinks(md)
        blocks = []
        for c in sorted(cs, key=lambda x: x["addr"]):
            safe = re.sub(r"[^A-Za-z0-9_]", "_", c["func"])
            dobj = f"src/{mod}/{safe}.o"   # doelpad in de delink-boom
            blocks += ["", f"src/{mod}/{safe}.c:", "    complete",
                       # end op 4 uitlijnen: bij een thumb-TU met niet-4-voud grootte
                       # horen de pad-bytes bij de TU; anders begint het volgende
                       # gap-object op een oneven adres, lijnt de linker het op 4 uit
                       # en schuift alles erna +2 (func_0200c46c-les, 2026-07-19)
                       f"    .text       start:0x{c['addr']:08x} end:0x{(c['addr']+c['size']+3)&~3:08x}"]
            if c.get("prebuilt"):
                prebuilt.append(f"{c['obj']}\t{dobj}")
            else:
                ext = "cpp" if c.get("cpp") else "c"
                rel = f"src/{mod}/{safe}.{ext}"
                dst = MKDS / rel
                dst.parent.mkdir(parents=True, exist_ok=True)
                shutil.copyfile(c["scratch"], dst)
                # 3e kolom: arm/thumb (mwcc heeft -thumb nodig voor thumb-functies)
                tus.append(f"{rel}\t{dobj}\t{mode_of(c)}\t{c.get('mwcc','')}")
        (md / "delinks.txt").write_text("\n".join(hdr + blocks) + "\n")
    TUS.write_text("\n".join(tus) + "\n" if tus else "")
    (MKDS / "ai/tus_prebuilt.txt").write_text("\n".join(prebuilt) + "\n" if prebuilt else "")
    inject_evidence(active)
    return active


def inject_evidence(active):
    """zet de `// bewijs:`-comment uit ai/names.jsonl bovenaan elke gegenereerde src/*.c.
    generate() overschrijft src/ uit de scratch, dus de annotatie moet hier opnieuw
    aangebracht worden (grootboek = bron van waarheid, blijft zo persistent)."""
    nf = MKDS / "ai/names.jsonl"
    if not nf.is_file():
        return
    ev = {}
    for line in nf.read_text().splitlines():
        if line.strip():
            r = json.loads(line)
            if r.get("bewijs") and not r.get("voorstel"):
                ev[r["func"]] = r["bewijs"]
    for c in active:
        b = ev.get(c["func"])
        if not b:
            continue
        safe = re.sub(r"[^A-Za-z0-9_]", "_", c["func"])
        for ext in ("c", "cpp"):
            p = MKDS / f"src/{c['module']}/{safe}.{ext}"
            if p.is_file():
                t = p.read_text()
                if "// bewijs:" not in t:
                    p.write_text(f"// bewijs: {b}\n{t}")
                break


def build():
    r = subprocess.run(["bash", "build.sh"], cwd=MKDS, capture_output=True, text=True, timeout=600)
    ok = "OK ===" in r.stdout
    return ok, r.stdout, r.stderr


def sha_ok():
    ok, out, err = build()
    return ok


MOD_BIN = {
    "arm9": ("build/eur/build/arm9.bin", "extract/eur/arm9/arm9.bin", 0x02000000),
    "itcm": ("build/eur/build/itcm.bin", "extract/eur/arm9/itcm.bin", 0x01FF8000),
}
for _i in range(4):
    MOD_BIN[f"ov{_i:03}"] = (f"build/eur/build/arm9_ov{_i:03}.bin",
                             f"extract/eur/arm9_overlays/ov{_i:03}.bin", None)


def differing_addrs(mod):
    """VMA's waar de gebouwde module afwijkt van het origineel."""
    bp, op, base = MOD_BIN[mod]
    b = (MKDS / bp).read_bytes()
    o = (MKDS / op).read_bytes()
    if base is None:
        # overlay-basis uit delinks.txt
        for line in (module_dir(mod) / "delinks.txt").read_text().splitlines():
            m = re.search(r"start:(0x\w+)", line)
            if m:
                base = int(m.group(1), 16)
                break
    return {base + i for i in range(min(len(b), len(o))) if b[i] != o[i]}


def bad_by_diff(active):
    """map afwijkende bytes op de TU's die dat adresbereik bezitten."""
    per_mod = {}
    for c in active:
        per_mod.setdefault(c["module"], []).append(c)
    bad = []
    for mod, cs in per_mod.items():
        diffs = differing_addrs(mod)
        if not diffs:
            continue
        for c in cs:
            rng = range(c["addr"], c["addr"] + c["size"])
            if any(a in diffs for a in rng):
                bad.append(c)
    return bad


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--generate", action="store_true")
    ap.add_argument("--build", action="store_true")
    ap.add_argument("--bisect", action="store_true")
    args = ap.parse_args()

    cands = load_candidates()
    quar = read_quarantine()
    print(f"{len(cands)} kandidaten, {len(quar)} in quarantaine")

    if args.generate:
        active = generate(cands, quar)
        print(f"{len(active)} TU's gegenereerd (src/ + delinks + tus.txt)")

    if args.build or args.bisect:
        ok, out, err = build()
        tail = "\n".join(out.strip().splitlines()[-4:])
        print(tail)
        if ok:
            active = [c for c in cands if c["addr"] not in quar]
            print(f"\n*** {len(active)} functies zitten byte-perfect IN de ROM ***")
            return

    if args.bisect:
        # ronde-voor-ronde: bouw; bij link-fout quarantaine op undefined-symbolen,
        # bij SHA1-diff quarantaine op afwijkend TU-adres; herhaal tot match.
        func_by_stem = {c["func"]: c for c in cands}
        for ronde in range(1, 12):
            active = [c for c in cands if c["addr"] not in quar]
            generate(cands, quar)
            ok, out, err = build()
            if ok:
                print(f"\n*** ronde {ronde}: {len(active)} functies zitten byte-perfect IN de ROM "
                      f"({len(quar)} geparkeerd) ***")
                return
            # 1) link-fouten? 'Referenced from "func" in obj.o'
            link_bad = set()
            for m in re.finditer(r'Referenced from "([^"]+)" in (\S+)\.o', out + err):
                stem = m.group(2).split("/")[-1]
                if stem in func_by_stem:
                    link_bad.add(func_by_stem[stem]["addr"])
                elif m.group(1) in func_by_stem:
                    link_bad.add(func_by_stem[m.group(1)]["addr"])
            if link_bad:
                names = [f"0x{a:08x}" for a in sorted(link_bad)]
                print(f"ronde {ronde}: link-fout, {len(link_bad)} TU('s) met "
                      f"ongedefinieerde symbolen -> quarantaine ({', '.join(names)})")
                quar |= link_bad
                QUAR.write_text("\n".join(f"0x{a:08x}" for a in sorted(quar)) + "\n")
                continue
            # 2) SHA1-diff? map afwijkende bytes op TU's
            bad = bad_by_diff(active)
            if not bad:
                print(f"\nronde {ronde}: SHA1 breekt maar geen TU wijkt af. Laatste build:")
                print("\n".join((out + err).strip().splitlines()[-6:]))
                return
            print(f"ronde {ronde}: {len(bad)} TU's byte-afwijkend -> quarantaine")
            quar |= {c["addr"] for c in bad}
            QUAR.write_text("\n".join(f"0x{a:08x}" for a in sorted(quar)) + "\n")


def bisect_bad(active, quar_base):
    """binair: vind de minimale set TU's die de SHA1 breekt."""
    def build_with(exclude):
        q = quar_base | {c["addr"] for c in exclude}
        generate([*active], q)
        return sha_ok()

    # als leeg toevoegen al matcht is er niets mis (zou niet hier komen)
    bad = []
    suspects = list(active)
    # iteratief: knip in tweeën, hou de helft die faalt
    def find_one(pool, keep_bad):
        """vind één slechte TU binnen pool, gegeven dat keep_bad al slecht is."""
        cur = list(pool)
        while len(cur) > 1:
            mid = len(cur) // 2
            left, right = cur[:mid], cur[mid:]
            # test met alleen 'left' actief bovenop reeds-goede: exclude right+overige
            exclude = right + keep_bad
            if build_with(exclude):
                # left alleen -> matcht? dan zit de boosdoener in right
                cur = right
            else:
                cur = left
        return cur[0]

    remaining = list(active)
    # zolang de volle actieve set (min gevonden bad) faalt, zoek nog één
    while True:
        if build_with(bad):
            break
        one = find_one([c for c in remaining if c not in bad], bad)
        bad.append(one)
        print(f"  boosdoener gevonden: 0x{one['addr']:08x} {one['func']}")
    return bad


if __name__ == "__main__":
    main()
