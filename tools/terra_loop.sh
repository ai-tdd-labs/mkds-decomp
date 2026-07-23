#!/bin/bash
# terra_loop.sh — één functie kraken met Codex Terra + externe oracle-feedback.
# Codex-sandbox blokkeert docker/wine, dus Terra schrijft alleen de kandidaat;
# de oracle (aimatch, wibo-backend) draait HIER en het verschil gaat terug via
# `codex exec resume`. Args: <addr> <func> <size> [max_rondes]
set -u
cd "$(dirname "$0")/.."
ADDR="$1"; FUNC="$2"; SIZE="$3"; MAXR="${4:-5}"; MODE="${5:-thumb}"; EFFORT="${6:-high}"
SRC="ai/scratch/agent_${ADDR#0x}.c"
BRIEF="ai/wave/brief_${ADDR#0x}.md"
PY=../st/.venv/bin/python
MODEL="gpt-5.6-terra"
EFF="$EFFORT"

oracle() {
  MKDS_CC=wibo $PY tools/aimatch.py --src "$SRC" --func "$FUNC" \
    --module arm9 --addr "$ADDR" --size "$SIZE" 2>&1
}

P0="Je bent een matching-decompilatie-agent voor Mario Kart DS (EUR).
Lees de brief ${BRIEF} volledig (disassembly, pool-woorden, callee-signaturen, codegen-trucs).
Schrijf C die byte-perfect naar de ROM-bytes van ${FUNC} @ ${ADDR} (size ${SIZE}, ${MODE}) compileert.
HARDE REGELS: strings/globals NOOIT als literal maar als extern data_<adres>-symbool
uit de brief; elke naam moet in config/eur/arm9/symbols.txt bestaan; callees exact
met brief-signaturen; eerste functieregel = '// PURPOSE: <één Engelse zin>'.
Schrijf je kandidaat NAAR HET BESTAND ${SRC} (overschrijf volledig). Verifieer NIET zelf
(geen docker). Antwoord alleen met 'GESCHREVEN'."

OUT=$(codex exec -m "$MODEL" -c model_reasoning_effort="$EFF" --sandbox workspace-write \
  --cd "$PWD" "$P0" < /dev/null 2>/tmp/terra_err_${ADDR#0x}.log)
SID=$(echo "$OUT" | grep -oE 'session[ _-]?id[: ]+[A-Za-z0-9-]+' | grep -oE '[A-Za-z0-9-]{8,}' | tail -1)

for r in $(seq 1 "$MAXR"); do
  RES=$(oracle)
  if echo "$RES" | grep -q "match=True"; then
    MW=$(echo "$RES" | grep -oE 'mwcc=[^ ]+' | head -1)
    echo "TERRA ${FUNC}: MATCH ronde ${r} ${MW}"
    exit 0
  fi
  DIFF=$(echo "$RES" | grep -iE "mismatch|byte|0x0[12][0-9a-f]{6}|expected|got|verschil" | head -30)
  FB="De oracle meldt GEEN match. Afwijkingen:
${DIFF}

Corrigeer ${SRC} (volledig overschrijven). Antwoord alleen met 'GESCHREVEN'."
  if [ -n "$SID" ]; then
    codex exec resume "$SID" -c model_reasoning_effort="$EFF" --sandbox workspace-write \
      --cd "$PWD" "$FB" < /dev/null > /dev/null 2>&1
  else
    codex exec -m "$MODEL" -c model_reasoning_effort="$EFF" --sandbox workspace-write \
      --cd "$PWD" "$FB" < /dev/null > /dev/null 2>&1
  fi
done
echo "TERRA ${FUNC}: GEEN-MATCH na ${MAXR} rondes"
exit 1
