#!/bin/bash
# terra_wave.sh — twee-fasen Terra-golf (eerste-pen-batch + herkansings-batch).
# Fase 1: elk doel precies ÉÉN codex-ronde, alles parallel (~110s totaal).
#         Matches direct klaar; missers -> ai/wave/terra_miss.txt (addr|sid|func|size|mode).
# Fase 2 (--retry): alle missers tegelijk één resume-ronde met hun oracle-diff.
# Wat na fase 2 (of 3) niet valt gaat naar de escalatie-bak, niet eindeloos malen.
# Doelenlijst: regels "addr func size mode" op stdin, of --retry [effort].
set -u
cd "$(dirname "$0")/.."
PY=../st/.venv/bin/python
MODEL="${TW_MODEL:-gpt-5.6-terra}"
MISS="ai/wave/terra_miss.txt"

oracle() { # addr func size
  MKDS_CC=wibo $PY tools/aimatch.py --src "ai/scratch/agent_${1#0x}.c" \
    --func "$2" --module arm9 --addr "$1" --size "$3" 2>&1
}

first_pen() { # addr func size mode effort
  local ADDR="$1" FUNC="$2" SIZE="$3" MODE="$4" EFF="$5"
  local SRC="ai/scratch/agent_${ADDR#0x}.c" BRIEF="ai/wave/brief_${ADDR#0x}.md"
  local s=$(date +%s)
  local P="Je bent een matching-decompilatie-agent voor Mario Kart DS (EUR).
Lees de brief ${BRIEF} volledig (disassembly, pool-woorden, callee-signaturen, codegen-trucs).
Schrijf C die byte-perfect naar de ROM-bytes van ${FUNC} @ ${ADDR} (size ${SIZE}, ${MODE}) compileert.
HARDE REGELS: strings/globals NOOIT als literal maar als extern data_<adres>-symbool
uit de brief; elke naam moet in config/eur/arm9/symbols.txt bestaan; callees exact
met brief-signaturen; eerste functieregel = '// PURPOSE: <één Engelse zin>'.
Schrijf je kandidaat NAAR HET BESTAND ${SRC} (overschrijf volledig). Verifieer NIET zelf
(geen docker). Ontdek je een NIEUWE codegen-truc (bronvorm die mwcc tot een
specifiek instructiepatroon dwingt en die nog niet in de brief staat), append
die dan als één JSON-regel aan ai/tricks.jsonl: {\"trick\": \"<korte naam>\",
\"uitleg\": \"<bronvorm -> instructie-effect>\", \"bron\": \"${FUNC}\"}.
Antwoord alleen met 'GESCHREVEN'."
  local OUT SID RES
  OUT=$(perl -e "alarm ${TW_ALARM:-240}; exec @ARGV" -- codex exec -m "$MODEL" -c model_reasoning_effort="$EFF" --sandbox workspace-write \
    --cd "$PWD" "$P" < /dev/null 2>&1)
  SID=$(echo "$OUT" | grep -oE 'session[ _-]?id[: ]+[A-Za-z0-9-]+' | grep -oE '[A-Za-z0-9-]{8,}' | tail -1)
  RES=$(oracle "$ADDR" "$FUNC" "$SIZE")
  if echo "$RES" | grep -q "match=True"; then
    echo "MATCH r1 ${FUNC}  [$(($(date +%s)-s))s]"
  else
    echo "${ADDR}|${SID}|${FUNC}|${SIZE}|${MODE}" >> "$MISS"
    mkdir -p ai/wave/nearmiss
    echo "$RES" > "ai/wave/nearmiss/${ADDR#0x}.txt"
    echo "miss  r1 ${FUNC}  [$(($(date +%s)-s))s] -> terra_miss.txt"
  fi
}

retry_one() { # missregel effort
  local ADDR SID FUNC SIZE MODE EFF="$2"
  IFS='|' read -r ADDR SID FUNC SIZE MODE <<< "$1"
  local SRC="ai/scratch/agent_${ADDR#0x}.c"
  local s=$(date +%s)
  local DIFF FB RES
  DIFF=$(oracle "$ADDR" "$FUNC" "$SIZE" | grep -iE "mismatch|byte|expected|got|verschil|0x0[12][0-9a-f]{6}" | head -30)
  FB="De oracle meldt GEEN match voor ${FUNC}. Afwijkingen:
${DIFF}

Corrigeer ${SRC} (volledig overschrijven). Antwoord alleen met 'GESCHREVEN'."
  if [ -n "$SID" ]; then
    perl -e "alarm ${TW_ALARM:-240}; exec @ARGV" -- codex exec resume "$SID" \
      -c model_reasoning_effort="$EFF" "$FB" < /dev/null > /dev/null 2>&1
  else
    perl -e "alarm ${TW_ALARM:-240}; exec @ARGV" -- codex exec -m "$MODEL" -c model_reasoning_effort="$EFF" --sandbox workspace-write \
      --cd "$PWD" "Lees ai/wave/brief_${ADDR#0x}.md. ${FB}" < /dev/null > /dev/null 2>&1
  fi
  RES=$(oracle "$ADDR" "$FUNC" "$SIZE")
  if echo "$RES" | grep -q "match=True"; then
    echo "MATCH retry ${FUNC}  [$(($(date +%s)-s))s]"
  else
    echo "${ADDR}|${SID}|${FUNC}|${SIZE}|${MODE}" >> "${MISS}.next"
    mkdir -p ai/wave/nearmiss
    echo "$RES" > "ai/wave/nearmiss/${ADDR#0x}.txt"
    echo "miss  retry ${FUNC}  [$(($(date +%s)-s))s]"
  fi
}

if [ "${1:-}" = "--retry" ]; then
  EFF="${2:-high}"
  [ -s "$MISS" ] || { echo "geen missers in $MISS"; exit 0; }
  rm -f "${MISS}.next"
  while IFS= read -r line; do
    [ -n "$line" ] && retry_one "$line" "$EFF" &
  done < "$MISS"
  wait
  mv -f "${MISS}.next" "$MISS" 2>/dev/null || : > "$MISS"
  echo "=== retry-fase klaar; resterende missers: $( [ -f "$MISS" ] && grep -c . "$MISS" || echo 0 )"
else
  EFF="${1:-high}"
  : > "$MISS"
  while read -r ADDR FUNC SIZE MODE; do
    [ -n "$ADDR" ] && first_pen "$ADDR" "$FUNC" "$SIZE" "$MODE" "$EFF" &
  done
  wait
  echo "=== fase 1 klaar; missers: $(grep -c . "$MISS" 2>/dev/null || echo 0) (herkans: tools/terra_wave.sh --retry)"
fi
