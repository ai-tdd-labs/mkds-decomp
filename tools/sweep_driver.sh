#!/bin/bash
# sweep_driver.sh — dé productie-lus als repo-script (overleeft sessies).
# Draait de volledige trechter-cyclus met alle hygiëne-regels uit ai/ROUTING.md:
#   laag 0 (familie-klonen) -> batches eerste pen -> skiplijst-discipline ->
#   oogst met WRONG-DEST-poort -> push alleen bij groen -> tijd-budget-bewaking.
#   tools/sweep_driver.sh [BATCHES=10] [MODEL=gpt-5.6-terra] [EFFORT=low] [MIN=0x24] [MAX=0x100]
# Telemetrie: ai/wave/quota_log.tsv (tijd, model, effort, batch, match, miss, sec)
set -u
cd "$(dirname "$0")/.."
PY=../st/.venv/bin/python
BATCHES="${1:-10}"; MODEL="${2:-gpt-5.6-terra}"; EFFORT="${3:-low}"
MINSZ="${4:-0x24}"; MAXSZ="${5:-0x100}"
QLOG="ai/wave/quota_log.tsv"
export MKDS_CC=wibo

say() { echo "[$(date +%H:%M:%S)] $*"; }

say "laag 0: familie-klonen..."
$PY tools/family_harvest.py --recent 150 2>&1 | tail -2

say "laag 0b: near-miss permuter-sweep..."
$PY tools/nearmiss_route.py 2>&1 | tail -2

for b in $(seq 1 "$BATCHES"); do
  $PY tools/wave_prep.py --count 20 --min "$MINSZ" --max "$MAXSZ" > /dev/null 2>&1
  : > /tmp/sweep_targets.txt
  for f in ai/wave/brief_*.md; do
    [ -f "$f" ] || continue
    a=$(basename "$f" .md); a=${a#brief_}
    line=$(grep -oE "(\S+) kind:function\((arm|thumb),size=(0x[0-9a-f]+)\) addr:0x0*$a\b" config/eur/arm9/symbols.txt | head -1)
    [ -z "$line" ] && continue
    nm=$(echo "$line" | awk '{print $1}')
    mode=$(echo "$line" | grep -oE '\((arm|thumb)' | tr -d '(')
    sz=$(echo "$line" | grep -oE 'size=0x[0-9a-f]+' | cut -d= -f2)
    echo "0x$a $nm $sz $mode" >> /tmp/sweep_targets.txt
  done
  [ -s /tmp/sweep_targets.txt ] || { say "band leeg"; break; }
  s=$(date +%s)
  OUT=$(TW_MODEL="$MODEL" TW_ALARM=$([ "$EFFORT" = "low" ] && echo 240 || echo 480) \
        bash tools/terra_wave.sh "$EFFORT" < /tmp/sweep_targets.txt 2>&1)
  el=$(($(date +%s)-s))
  M=$(echo "$OUT" | grep -c "^MATCH r1"); X=$(echo "$OUT" | grep -c "^miss")
  say "batch $b/$BATCHES: $M match / $X miss  [${el}s]"
  printf '%s\t%s\t%s\t%d\t%d\t%d\t%d\n' "$(date +%F_%T)" "$MODEL" "$EFFORT" "$b" "$M" "$X" "$el" >> "$QLOG"
  if [ "$M" -eq 0 ] && echo "$OUT" | grep -qiE "rate.?limit|quota|429|too many"; then
    say "QUOTA-STOP"; break
  fi
  # hygiëne: alles direct naar de skiplijst (dubbel-werk-les 2026-07-19)
  cut -d'|' -f1 ai/wave/terra_miss.txt >> ai/wave/skip.txt 2>/dev/null
  cat ai/wave/terra_miss.txt >> ai/wave/terra_miss_all.txt 2>/dev/null
  awk '{print $1}' /tmp/sweep_targets.txt >> ai/wave/skip.txt
  sort -u ai/wave/skip.txt -o ai/wave/skip.txt
done

say "oogst (met WRONG-DEST-poort)..."
$PY tools/register_batch.py --glob 'ai/scratch/agent_*.c' 2>&1 | tail -1
OUT=$($PY tools/hangin.py --generate --build 2>&1 | tail -3)
echo "$OUT"
if echo "$OUT" | grep -q "OK ==="; then
  git add -A && git commit -q -m "Sweep-driver harvest ($MODEL/$EFFORT)

Co-Authored-By: Claude Fable 5 <noreply@anthropic.com>" && \
    git push -q origin main && bash tools/push_public.sh "Sweep-driver harvest" && say "gepusht"
else
  say "VERSCHIL — diagnose nodig (uitgepakte bins diffen, .L-label-truc); NIET gepusht"
fi
