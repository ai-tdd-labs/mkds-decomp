# Ombouw-batch runbook (>95%-bijna-treffers automatisch matchen)

De >95%-bijna-treffers uit `ai/sdk_nearhits.json` zijn SDK-functies waarvan de
bron (uit een buur-decomp) al bijna klopt — alleen een revisieverschil. Die kraak
je via de OMBOUW-workflow (bron aanpassen), NIET de permuter (die is voor
register-coloring near-misses).

Gemeten: batch #1 = 6/6, allemaal eerste poging, ~90 s/functie.

## Zo draai je een batch (per ~6 tegelijk, wine aankan)

1. Kandidaten kiezen (hoogste score eerst):
   ```sh
   python3 -c "import json; [print(h['score'], h['mkds'], h['func'], h['bron'].split('/')[-1]) \
     for h in json.load(open('ai/sdk_nearhits.json'))[:12]]"
   ```

2. Per kandidaat een agent (via het Agent-tool of Workflow), met dit stramien
   (MODEL: Sonnet 5 default; Fable-high alleen als de bron structureel afwijkt):
   - Lees de bron (`func`-veld) uit het bron-project (khdays/pokediamond/...).
   - `tools/aiworklist.py row <mkds-naam>` voor doel-disasm.
   - Zelfstandige kandidaat naar `ai/scratch/ob_<addr>.c`; volg de diff (2005-vs-2006-revisie).
   - Verifieer: `tools/aimatch.py --src ... --func <mkds-naam>` (RESULT match=True vereist).
   - Bij calls: `tools/linkcheck.py --src ... --func <mkds-naam>` (WRONG-DEST-gate).
   - Max 6 pogingen, stop na 2 niet-verbeterende. Lees mkds/notes/ bij vastlopen.

3. Na de batch: matches in `ai/matched.jsonl` schrijven, `tools/clone.py` draaien
   (gratis vermenigvuldiging), notes minen.

## Waarom niet één script dat alles blind doet
Elke ombouw vereist het LEZEN van een diff en een gerichte broncode-aanpassing —
dat is agent-werk (redeneren), geen vaste transformatie. De permuter (tools/permute.py)
is wél volautomatisch, maar alleen voor register-coloring near-misses, niet voor deze
revisie-verschillen. Halen dus verschillende soorten kandidaten.

## Machine
Wine timeout't onder zware belasting (swap vol). Herstart vóór een grote batch;
draai ~4 agents parallel (wine max -j4), niet 10.
