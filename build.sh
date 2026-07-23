#!/bin/bash
# build.sh — MKDS-buildketen (dsd + mwldarm), baseline-proef.
# delink -> lcf -> link (mwldarm) -> rom config -> rom build -> sha1.
set -e
cd "$(dirname "$0")"
ST=../st
DSD=$ST/dsd
WINE=/opt/homebrew/bin/wine
# Backend: MKDS_CC=wibo draait mwcc/mwld via qemu-i386+wibo in de mkds-cc
# container (zelfde absolute pad gemount) — veel sneller dan wine.
MKDS_CC="${MKDS_CC:-wine}"
run_pe() { # $1 = pad naar .exe; rest = argumenten
  local exe="$1"; shift
  if [ "$MKDS_CC" = "wibo" ]; then
    docker exec -w "$PWD" "${MKDS_WIBO_CONTAINER:-mkds-cc}" \
      qemu-i386-static /usr/local/bin/wibo-i686 "$PWD/$exe" "$@"
  else
    $WINE "$exe" "$@"
  fi
}
# Compiler: prefer the repo-vendored copy (tools/mwccarm/), fall back to ../st.
mwcc_path() { # $1 = version/exe relative path
  if [ -f "tools/mwccarm/$1" ]; then echo "tools/mwccarm/$1"; else echo "$ST/tools/mwccarm/$1"; fi
}
MWLD="$(mwcc_path 1.2/sp2p3/mwldarm.exe)"
CFG=config/eur/arm9/config.yaml
B=build/eur

echo "[0/6] doctor (consistentie-preflight, 0.2s)"
# vang naam-drift/orphan-refs VOORDAT we 5 min bouwen
$ST/.venv/bin/python tools/doctor.py --quiet || { echo "  === DOCTOR FAALT: fix eerst (zie hierboven) ==="; exit 1; }

echo "[1/6] delink"
rm -f mkds_eur.nds   # anders maskeert een oude ROM een gefaalde link als 'SHA-match'
# schoon: dsd ruimt objecten van een oude sectie-indeling niet op -> dubbele definities
rm -rf $B/delinks
# -M: ook $d op data-symbolen, anders krijgt mwld's interworking-moduskaart
# gaten in onontgonnen regio's -> spurieuze veneers/thumb-bits
$DSD delink --config-path $CFG --all-mapping-symbols >/dev/null 2>&1 || true

echo "[2/6] lcf"
$DSD lcf --config-path $CFG >/dev/null 2>&1
# KEEP_SECTION verbreden: mwld dead-stript TU's die alleen via reloc-loze
# data-pointers worden aangeroepen (pool-constante i.p.v. reloc) -> hele
# arm9-layout schuift op ("breker-regio's"). De originele ROM bevat die bytes
# hoe dan ook, dus niets mag gestript worden.
python3 - <<'KEEPEOF'
p = "build/eur/arm9.lcf"
t = open(p).read()
old = "KEEP_SECTION {\n    .init,\n    .ctor\n}"
new = "KEEP_SECTION {\n    .init,\n    .ctor,\n    .text,\n    .rodata,\n    .data,\n    .bss\n}"
if old in t:
    open(p, "w").write(t.replace(old, new))
elif ".text," not in t.split("SECTIONS")[0]:
    raise SystemExit("KEEP_SECTION-blok niet gevonden in arm9.lcf — dsd-formaat gewijzigd?")
KEEPEOF

echo "[2b/6] compileer gematchte TU's (met content-hash-cache)"
# elke matched TU: bron in src/, doel-object op het delink-pad dat de lcf verwacht.
# ai/tus.txt = regels 'bronpad<TAB>objectpad-relatief-tov-delinks' (leeg = niets te doen)
# Cache: sleutel = sha1(bron); ongewijzigde .c wordt gekopieerd i.p.v. hercompileren.
MWCC="$(mwcc_path 1.2/sp2p3/mwccarm.exe)"
CFLAGS="-O4,p -enum int -lang c99 -char signed -interworking -proc arm946e -gccext,on -msgstyle gcc"
$ST/.venv/bin/python tools/batch_compile.py || { echo "  === COMPILE-FOUT ==="; exit 1; }

# prebuilt SDK-objecten (geëmit door sdk_hangin.py) op hun delink-plek zetten
if [ -f ai/tus_prebuilt.txt ]; then
  m=0
  while IFS=$'\t' read -r obj dest; do
    [ -z "$obj" ] && continue
    cp "$obj" "$B/delinks/$dest"
    m=$((m+1))
  done < ai/tus_prebuilt.txt
  echo "    $m prebuilt SDK-object(en) geplaatst"
fi

echo "[3/6] link (mwldarm)"
# objectenlijst = alle gedelinkte objecten (gap + evt. gecompileerde TU's)
find $B/delinks -name "*.o" | sort > $B/objects.txt
rm -f $B/arm9.o   # anders maskeert een stale object een link-fout
# || true: mwld geeft exit 1 bij link-fouten; zonder dit doodt set -e het
# script stil VOORDAT de foutmelding hieronder geprint wordt
LINKLOG=$(run_pe "$MWLD" -proc arm946e -nostdlib -interworking \
    -map closure,unused -m Entry -msgstyle gcc @$B/objects.txt $B/arm9.lcf -o $B/arm9.o 2>&1) || true
echo "$LINKLOG" | grep -vE "MWCIncludes|fixme|wow64|err:environ|wineserver" || true
if [ ! -f $B/arm9.o ] || echo "$LINKLOG" | grep -q "Link failed"; then
    echo "  === LINK MISLUKT (geen arm9.o) ==="
    exit 1
fi

echo "[4/6] rom config + build"
RUST_LOG=warn $DSD rom config --elf $B/arm9.o --config $CFG >/dev/null 2>&1
RUST_LOG=warn $DSD rom build --config $B/build/rom_config.yaml --rom mkds_eur.nds \
    --arm7-bios arm7_bios.bin >/dev/null 2>&1

echo "[5/6] padding-stempel (gemengde pad-waarden die ds-rom niet kan uitdrukken)"
$ST/.venv/bin/python tools/fix_padding.py mkds_eur.nds extract/baserom_mkds_eur.nds

echo "[6/6] sha1"
python3 - <<PYEOF
import hashlib, pathlib
want = pathlib.Path("extract/baserom_mkds_eur.nds")
got = pathlib.Path("mkds_eur.nds")
if not got.is_file():
    print("  FOUT: geen mkds_eur.nds gebouwd"); raise SystemExit(1)
h_want = hashlib.sha1(want.read_bytes()).hexdigest() if want.is_file() else "?"
h_got = hashlib.sha1(got.read_bytes()).hexdigest()
print(f"  origineel: {h_want}")
print(f"  herbouwd:  {h_got}")
print("  === mkds_eur.nds: OK ===" if h_want == h_got else "  === VERSCHIL === (draai: tools/diffmap.py)")
PYEOF
