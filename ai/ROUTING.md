# ROUTING.md — gemeten AI-model/effort-lessen (het "tricks.jsonl" voor de vloot)

Regels: alleen GEMETEN lessen (datum + cijfers erbij). Meten is de oracle —
geen aannames zonder batch-cijfers. Nieuwe les? Append met datum en meting.

## De escalatie-ladder (2026-07-20, gemeten)

1. **Terra-low, verse pen** — massaproductie. 80%+ bovenin een verse band,
   zakt naar ~20% als de band afgeroomd is (dan band wisselen of oogsten).
2. **Ander model, verse pen** (SOL-high) — 58-80% van de weigeraars.
3. **Zelfde model high, verse pen** — 60% van de weigeraars.
4. **Resume-retry (met oracle-diff)** — alléén voor near-misses: low 35%,
   high 51%. Verse pen verslaat resume op harde gevallen: het anker aan de
   eigen mislukte poging is de echte rem.
5. **Fable/K3-max/permuter-sweep** — muren-klasse (epilogue/register/scheduler),
   zie tricks.jsonl en de muren-dossiers.

**Residu-les (2026-07-20): het "harde residu" na de codex-cascade is
ANALYSE-klasse, geen muur-klasse — Fable-low 12/12 op SDK OS/Fs-functies
(0x7c-0xb4) waar Terra én SOL meermaals op faalden, in 1-11 runs, mét 9
nieuwe trucs als bijvangst.** Kenmerk van de klasse: volatile/MMIO-semantiek,
64-bit RMW, struct-basispointer-keuzes — dingen die begrip vragen, geen
vormen-loterij. Routing: codex-cascade eerst (goedkoop volume), daarna residu
in Fable-low-batches van ~12; K3/permuter alleen voor wat Fable óók laat
liggen. Valkuil: Fable-agents die aimatch in background draaien blijven
"wachten" — instrueer SYNCHROON verifiëren (of por ze met SendMessage).
**SOL-xhigh + iteratieve verse-pen-lus (tools/codex_iter.sh, gemeten
2026-07-20): 8/12 op hetzelfde residu waar Fable-low 12/12 deed** — verse
sessie per ronde met de vorige oracle-diff als DATA in de prompt (geen
resume-anker). Iets trager en 4 G2d-achtigen bleven staan, maar draait
volledig op codex-quota. Beleid bij schaars Claude-budget: SOL-xhigh-iter is
het residu-werkpaard; Fable alleen orkestratie + de allerlaatste muren.
**Kernles: cascade > model-keuze.** Elke laag vangt ~60% van wat de vorige
liet liggen, en de faal-patronen verschillen per model — dus verse pen bij een
ánder model is bijna gratis extra dekking. Model-verschil binnen een laag is
klein (paar %), de verse pen doet het werk.

## Model-tabel (gemeten)

| Model | Rol | Meting |
|---|---|---|
| Terra-low | eerste-pen-massa | 35-110s/f, 80%→20% naarmate band leegraakt |
| Terra-high vers | tweede kans zelfde pool | 60% op weigeraars |
| SOL-high vers | tweede kans, ander faal-patroon | 58-80% op weigeraars |
| Sonnet 5 | Claude-werkpaard (aparte pool) | 30/34 in waves, nul link-fouten |
| Fable-low | pionier verse families + ontdekt trucs | 14/14 verse thumb; 4/4 muren-dossiers |
| Fable-high | muren | enige die alle 3 muur-klassen kraakt |
| K3-max | epilogue-muren | 1/84-muur eerste worp; ~2% weekquota/muur |
| Haiku/K3-low | niet inzetten | gemeten te zwak |
| Luna (alle efforts) | niet inzetten | eerlijke 3x10-test 2026-07-20: low 0/10, medium 4/10, high 4/10 — medium+ nodig om Terra-LOW te evenaren, en trager |
| Opus | diepe diagnose, geen volume | traag, meeste muren |

## Effort- en timeout-regels

- Effort low voor eerste pen; high pas bij de tweede laag. High op makkelijk
  werk = verspilling (zelfde uitkomst, meer quota).
- Timeout per agent-call: 240s (klein werk), 480s (groot/high) — codex kan
  hangen (13 min, 0 CPU); perl-alarm om élke call (TW_ALARM).
- Grote functies (0x100-0x200): met 1500-register-briefs + SOL-xhigh-ITER wél
  werkbaar: 40-80% per batch (was 0/10 bij register ~1200 met kale eerste
  pen) — het vliegwiel opent bands die eerder dicht zaten; hertest gesloten
  bands na elke ~300 nieuwe registraties. Volgende trap 0x200-0x400: 0/10 op
  xhigh-iter bij register 1557 (2026-07-21) — plafond; wacht op groter
  vliegwiel of Fable.

## Oudere gemeten lessen (2026-07-16 t/m 19, uit de model-vergelijkingen)

- **De register-allocatie-muur is model-onafhankelijk** — Fable, SOL en Opus
  strandden op exact dezelfde functies. Muren zijn compiler-terrein: alleen
  trucs/permuter-sweep breken ze, geen slimmer model.
- **Briefing > model**: de anti-verzin-regel ("elke symboolnaam moet in
  config/eur/arm9/symbols.txt bestaan; pool-slot zonder reloc = constante,
  schrijf als literal") elimineerde ALLE link-fouten. Altijd in agent-prompts.
- **coddog-voorbeelden schalen de goedkope vloot**: SOL ging van 1/9 (kaal)
  naar 3/4 met few-shot-broertjes in de brief.
- **Fable** herkent functie-semantiek het best en is de enige die de
  kennisbank goed vult (trucs ontdekken); low ≈ high op ontdekken (4/4 kale
  muren-dossiers op low) maar veel goedkoper.
- **Opus 4.8**: diepste analyses (vond o.a. dat agbcc géén instructie-scheduler
  heeft), maar traag en meeste muren — diagnose-rol, nooit volume.
- **Terra**: sterk op NDS/mwcc (3/3 destijds, vandaag bevestigd), zwak op GBA/
  agbcc-vormgevechten (1/3) — platform maakt uit bij codex-modellen.
- **K3 (kimi)**: alleen -max inzetten (low 0/3, high faalt op register/
  scheduler-klassen); -max kraakte de 1/84-epilogue-muur eerste worp (117s,
  ~2% weekquota op het $19-plan). CLI: `kimi -p` (géén -y/--auto erbij),
  resume `kimi -r <sid>`, effort via config default_effort.
- **SOL destijds**: 10/13 in 5m12s parallel, alles eerste worp; toen leken
  feedback-rondes niets te converteren — de nuance van vandaag: RESUME-retry
  converteert near-misses (51% op high), verse pen converteert harde gevallen.
- **Doorvoer-optimum Claude-vloot**: 12-14 agents/wave; oogst (~11-13 min) is
  het plafond → waves overlappen; pijplijn-modus met vroeg-stoppen haalde
  ~78 f/u. Haiku per functie zelfs trager dan Sonnet (6-12 min) + valse opgaves.

## Tijd-budgetten (gemeten — hanger-detectie is een LES, geen gevoel)

| Operatie | Normaal | Hanger-drempel |
|---|---|---|
| Terra-low pen (klein, ≤0x100) | 35-110s | >240s → alarm doodt |
| Terra/SOL-high pen | 90-270s | >480s → alarm doodt |
| Batch van 20 parallel | 2-5 min (low) / 6-8 min (high) | >2× normaal |
| Oracle-run (wibo) | 2-10s | >150s (aimatch-timeout) |
| Volledige build (wibo, warm) | ~2,5 min | >8 min |
| Oogst (register ~100 + build + push) | 5-10 min | >20 min |
| Sweep 13 brokken high + oogsten | 1,5-2 uur | — (per brok bewaken) |

Regel: bewaak op "geen nieuwe output in 15 min", NIET op totale duur — een
lange taak die gestaag logt is gezond (SOL-sweep 2 uur = normaal); een korte
taak zonder output is stuk (codex-hanger: 13 min, 1,8s CPU). Duur-checks:
mtime van de log/artefacten + CPU-tijd van het proces, nooit alleen de klok.

## Batch-hygiëne

- Gekraakt of gemist: adres DIRECT naar ai/wave/skip.txt (register loopt achter
  tot de oogst; anders dubbel werk — 3 batches verspild op 2026-07-19).
- Missers naar ai/wave/terra_miss_all.txt (addr|sid|func|size|mode) voor de
  volgende trechter-laag.
- Oogst per ~100, niet per batch (oogst is serieel; build-kosten vast).
- Driver-scripts: buitentimeout + heartbeat — nooit wachten op alleen een
  taak-notificatie (5 uur verloren aan een hanger, nacht 19→20 jul).

## Cross-platform (2026-07-23, volledig rapport: ~/projects/decomp/PLATFORM_BENCHMARK.md)
- N64/IDO (Wave Race): 76% (13/17); routing OMGEKEERD aan NDS — SOL-high/
  xhigh 7/7, Terra-low 2/5. GC/C++ (Sunshine): vers ~11%, near-miss ~67%.
- Kernles: taal > console (C fabriek-vriendelijk, C++ zwaar); routing per
  platform apart meten; oracle-snelheid bepaalt het iteratietempo.
- Drie fabrieken operationeel: mkds (NDS), ai-tdd-labs/wave-race-64-ai
  (N64, 49 IDO-trucs), sms (GC, near-miss-inzet).
