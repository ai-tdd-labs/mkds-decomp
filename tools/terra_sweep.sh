#!/bin/bash
# terra_sweep.sh — massale eerste-pen-sweep met Terra-low (fase-1-only).
# Per batch: wave_prep 20 doelen -> terra_wave fase 1 (parallel, ~1-2 min) ->
# matches naar de oogst-wachtrij, missers naar ai/wave/skip.txt (herkansing later).
# Elke HARVEST_EVERY batches: register_batch + hangin + build; alleen bij groene
# SHA1 wordt gepusht. Stopt bij codex-quota/rate-fouten of na MAX_BATCHES.
#   tools/terra_sweep.sh [MAX_BATCHES] [HARVEST_EVERY] [EFFORT]
set -u
cd "$(dirname "$0")/.."
PY=../st/.venv/bin/python
MAXB="${1:-10}"
HARVEST_EVERY="${2:-5}"
EFF="${3:-low}"
LOG="ai/wave/sweep_log.txt"
SKIP="ai/wave/skip.txt"
export MKDS_CC=wibo

say() { echo "[$(date +%H:%M:%S)] $*" | tee -a "$LOG"; }

harvest() {
  say "OOGST: registreren + inhangen + bouwen..."
  $PY tools/register_batch.py --glob 'ai/scratch/agent_*.c' >> "$LOG" 2>&1
  OUT=$($PY tools/hangin.py --generate --build 2>&1 | tail -4)
  echo "$OUT" >> "$LOG"
  if echo "$OUT" | grep -q "byte-perfect IN de ROM"; then
    N=$(echo "$OUT" | grep -oE '[0-9]+ functies' | head -1)
    say "OOGST GROEN: $N — push"
    git add -A
    git commit -q -m "Terra-low sweep harvest: ROM stays byte-perfect

Automated first-pen sweep (tools/terra_sweep.sh); misses deferred to
ai/wave/skip.txt for a later retry round.

Co-Authored-By: Claude Fable 5 <noreply@anthropic.com>" && \
      git push -q origin main && git push -q public main && say "gepusht"
  else
    say "OOGST BREEKT — sweep stopt voor diagnose"; echo "$OUT"; exit 1
  fi
}

for b in $(seq 1 "$MAXB"); do
  say "=== batch $b/$MAXB: briefs prepped..."
  PREP=$($PY tools/wave_prep.py --count 20 --min 0x24 --max 0xa0 2>&1)
  echo "$PREP" >> "$LOG"
  # doelenlijst uit de briefs afleiden
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
  NT=$(grep -c . /tmp/sweep_targets.txt || true)
  [ "$NT" -eq 0 ] && { say "geen doelen meer — sweep klaar"; break; }
  say "batch $b: $NT doelen, fase 1 op $EFF..."
  OUT=$(bash tools/terra_wave.sh "$EFF" < /tmp/sweep_targets.txt 2>&1)
  echo "$OUT" >> "$LOG"
  M=$(echo "$OUT" | grep -c "^MATCH r1" || true)
  X=$(echo "$OUT" | grep -c "^miss" || true)
  say "batch $b: $M match / $X miss"
  # rate/quota-detectie: als ALLES miste én codex fouten gaf, stoppen
  if [ "$M" -eq 0 ] && echo "$OUT" | grep -qiE "rate.?limit|quota|429|too many"; then
    say "QUOTA/RATE-LIMIT gedetecteerd — sweep stopt"; break
  fi
  # missers definitief naar de skiplijst (herkansing later via terra_wave --retry)
  if [ -s ai/wave/terra_miss.txt ]; then
    cut -d'|' -f1 ai/wave/terra_miss.txt >> "$SKIP"
    cat ai/wave/terra_miss.txt >> ai/wave/terra_miss_all.txt
  fi
  # matches OOK naar de skiplijst: het register loopt tot de oogst achter,
  # anders kiest wave_prep dezelfde net-gekraakte functies opnieuw (dubbel werk)
  awk '{print $1}' /tmp/sweep_targets.txt >> "$SKIP"
  sort -u "$SKIP" -o "$SKIP"
  if [ $((b % HARVEST_EVERY)) -eq 0 ]; then harvest; fi
done
harvest
say "=== SWEEP KLAAR ==="
