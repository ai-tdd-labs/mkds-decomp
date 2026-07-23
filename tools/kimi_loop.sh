#!/bin/bash
# kimi_loop.sh — K3 (kimi) op één muur-functie, met externe oracle-feedback.
# K3-max is de muren-specialist (epilogue-klasse: 1/84-muur eerste worp, 117s)
# maar kost ~2% weekquota per muur op het $19-plan — ALLEEN inzetten op
# functies waar de hele trechter (klonen/Terra/SOL/permuter/Fable) op faalde.
# CLI-lessen (ai/ROUTING.md): `kimi -p` (NOOIT -y/--auto erbij — botst);
# resume: `kimi -r <session_id>`; effort via config default_effort (staat op max).
#   tools/kimi_loop.sh <addr> <func> <size> [max_rondes=3] [mode=thumb]
set -u
cd "$(dirname "$0")/.."
ADDR="$1"; FUNC="$2"; SIZE="$3"; MAXR="${4:-3}"; MODE="${5:-thumb}"
SRC="ai/scratch/agent_${ADDR#0x}.c"
BRIEF="ai/wave/brief_${ADDR#0x}.md"
PY=../st/.venv/bin/python
KIMI="$HOME/.kimi-code/bin/kimi"

oracle() {
  MKDS_CC=wibo $PY tools/aimatch.py --src "$SRC" --func "$FUNC" \
    --module arm9 --addr "$ADDR" --size "$SIZE" 2>&1
}

P0="Je bent een matching-decompilatie-agent voor Mario Kart DS (EUR).
Lees ${BRIEF} volledig (disassembly, pool-woorden, callee-signaturen, trucs)
en het residu-dossier als dat er is. Schrijf C die byte-perfect naar
${FUNC} @ ${ADDR} (size ${SIZE}, ${MODE}) compileert.
HARDE REGELS: symbolen alleen uit config/eur/arm9/symbols.txt; strings/globals
als extern data_<adres>; eerste regel '// PURPOSE: <één Engelse zin>'.
Schrijf je kandidaat naar ${SRC}. Verifieer niet zelf. Antwoord 'GESCHREVEN'."

OUT=$(perl -e "alarm ${TW_ALARM:-600}; exec @ARGV" -- "$KIMI" -p "$P0" < /dev/null 2>&1)
SID=$(echo "$OUT" | grep -oiE "session[ _-]?id[: ]+[A-Za-z0-9-]+" | grep -oE '[A-Za-z0-9-]{8,}' | tail -1)

for r in $(seq 1 "$MAXR"); do
  RES=$(oracle)
  if echo "$RES" | grep -q "match=True"; then
    echo "K3 ${FUNC}: MATCH ronde ${r}"
    exit 0
  fi
  mkdir -p ai/wave/nearmiss
  echo "$RES" > "ai/wave/nearmiss/${ADDR#0x}.txt"
  DIFF=$(echo "$RES" | grep -iE "mismatch|byte|expected|got|verschil" | head -30)
  FB="Oracle: GEEN match voor ${FUNC}. Afwijkingen:
${DIFF}
Corrigeer ${SRC} (volledig overschrijven). Antwoord 'GESCHREVEN'."
  if [ -n "$SID" ]; then
    perl -e "alarm ${TW_ALARM:-600}; exec @ARGV" -- "$KIMI" -r "$SID" -p "$FB" < /dev/null > /dev/null 2>&1
  else
    perl -e "alarm ${TW_ALARM:-600}; exec @ARGV" -- "$KIMI" -p "Lees ${BRIEF}. ${FB}" < /dev/null > /dev/null 2>&1
  fi
done
echo "K3 ${FUNC}: GEEN-MATCH na ${MAXR} rondes"
exit 1
