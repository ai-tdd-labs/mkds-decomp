#!/bin/bash
# codex_iter.sh — Fable-stijl iteratieve lus, maar met codex (quota-vriendelijk).
# Les 2026-07-20: resume-anker remt (35-51%) maar verse pen wint (58-80%), én
# Fable's 12/12 kwam deels uit de iteratieve oracle-lus. Dit combineert beide:
# elke ronde een VERSE codex-sessie, met de oracle-diff van de vorige poging
# als data in de prompt (geen sessie-anker, wel de feedback).
#   tools/codex_iter.sh <addr> <func> <size> [mode=arm] [rondes=5] [model] [effort]
set -u
cd "$(dirname "$0")/.."
ADDR="$1"; FUNC="$2"; SIZE="$3"; MODE="${4:-arm}"; MAXR="${5:-5}"
MODEL="${6:-gpt-5.6-sol}"; EFF="${7:-xhigh}"
SRC="ai/scratch/agent_${ADDR#0x}.c"
BRIEF="ai/wave/brief_${ADDR#0x}.md"
PY=../st/.venv/bin/python

oracle() {
  MKDS_CC=wibo $PY tools/aimatch.py --src "$SRC" --func "$FUNC" \
    --module arm9 --addr "$ADDR" --size "$SIZE" 2>&1
}

FEEDBACK=""
for r in $(seq 1 "$MAXR"); do
  P="Je bent een matching-decompilatie-agent voor Mario Kart DS (EUR).
Lees ${BRIEF} volledig (disassembly, pool-woorden, callee-signaturen, trucs in
de brief én ai/tricks.jsonl). Schrijf C die byte-perfect compileert naar
${FUNC} @ ${ADDR} (size ${SIZE}, ${MODE}).
HARDE REGELS: symbolen alleen uit config/eur/arm9/symbols.txt; pool-slot
zonder reloc = literal; MMIO = volatile-pointer-literal; eerste regel
'// PURPOSE: <één Engelse zin>'.${FEEDBACK}
Schrijf je kandidaat naar ${SRC} (volledig overschrijven). Verifieer niet
zelf. Ontdek je een nieuwe codegen-truc: append als JSON-regel aan
ai/tricks.jsonl. Antwoord alleen 'GESCHREVEN'."
  perl -e "alarm ${TW_ALARM:-480}; exec @ARGV" -- codex exec -m "$MODEL" \
    -c model_reasoning_effort="$EFF" --sandbox workspace-write \
    --cd "$PWD" "$P" < /dev/null > /dev/null 2>&1
  RES=$(oracle)
  if echo "$RES" | grep -q "match=True"; then
    echo "ITER ${FUNC}: MATCH ronde ${r} (${MODEL}/${EFF})"
    exit 0
  fi
  DIFF=$(echo "$RES" | grep -iE "mismatch|byte|expected|got|verschil" | head -25)
  [ -f "$SRC" ] && VORIGE=$(head -60 "$SRC") || VORIGE="(geen)"
  FEEDBACK="

EERDERE POGING (ter info — begin VERS, kopieer niet blind):
\`\`\`c
${VORIGE}
\`\`\`
Oracle-afwijkingen van die poging:
${DIFF}"
  mkdir -p ai/wave/nearmiss
  echo "$RES" > "ai/wave/nearmiss/${ADDR#0x}.txt"
done
echo "ITER ${FUNC}: GEEN-MATCH na ${MAXR} rondes (${MODEL}/${EFF})"
exit 1
