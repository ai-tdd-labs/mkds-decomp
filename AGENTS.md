# MKDS matching-decomp — operationele regels (geleend van sm64ds, aangepast)

Gebaseerd op sm64ds-decomp/notes/crack-loop-runbook.md + AGENTS.md. Alleen de
regels die op onze greenfield-MKDS van toepassing zijn; hun claims-API en exacte
size-banden zijn overgeslagen.

## De onwrikbare regel
Nooit "match" claimen zonder letterlijke `RESULT match=True` van tools/aimatch.py.
Elke bewering is een hypothese tot het orakel spreekt. Geldt voor mij én elke agent.

## Model-routing (sm64ds' GEMETEN bevindingen — corrigeert mijn eerdere aanname)
- **Sonnet 5 = gevalideerde default** voor matching: pariteit met Opus 4.8 op ~halve kosten.
  Dus NIET standaard Opus draaien (dat deed ik fout: overkill op makkelijke functies).
- **Fable 5 (effort high) = de mid-band vormmuur** (functies waar structuur-reconstructie nodig is,
  coddog-sim laag): 75-100% waar andere modellen ~5% floorden. Bewaar Fable voor het echte werk.
- **Opus→Fable two-stage** voor drie-keer-gedraineerde harde banden.
- Simpele SDK-ombouw (>90% al gelijk): licht model is genoeg.
- Geef agents dus expliciet `model`/`effort` mee per taaksoort, niet één model voor alles.

## Batch-discipline
1. **Worklist ELKE batch opnieuw bouwen** — het corpus verandert als functies landen, dus de
   beste siblings veranderen. (crossgame.py / aicoddog.py opnieuw draaien.)
2. **Banken is DRY-RUN by default**, `--apply` om echt te schrijven. Nooit blind toepassen.
3. **Vroege stop**: agent stopt na 2 niet-verbeterende pogingen, rapporteert beste versie.
4. **Alleen dichte missers parken** (div ≤ 12) in de near-miss-bank; een functie die de run
   gewoon faalde gaat terug de pool in.
5. **Na ELKE batch: mine de notes** — elke werkende hefboom → ai/notes.md; elke herhaalde
   floor-vorm documenteren zodat agents er niet op blijven duwen.
6. **Mechanische fix eerst sweepen** over de near-miss-bank vóór je tokens uitgeeft (een nieuw
   idioom kan oude drafts retroactief matchen — nul kosten).
7. **Two-stage retry**: eerst landen+banken, DAN de missers opnieuw — die vinden de vers-gebankte
   familieleden in src/ en kopiëren het werkende idioom.

## Floor (NIET op grinden, naar hand-fix)
Base-materialisatie-RMW, instructie-ordening/scheduling, pure register-kleuring-swaps,
store-emissievolgorde. Bewezen onbereikbaar vanuit C over compilerversies + permuter heen.
Onze fader-familie (st) en de MKDS-memset zijn hiervan voorbeelden.

## Nog te bouwen (sm64ds heeft ze, wij nog niet)
- **linkcheck**: reconstrueer gelinkte bytes → vangt verkeerde-callee die het gewildcarde
  orakel mist (WRONG-DEST). Belangrijk vóór we ergens een PR van maken.
- **clone/paramclone**: gratis post-pass — ongematchte functie identiek aan gematchte
  (op relocaties/immediates na) → hergebruik de bron, nul tokens.
- **permuter**: voor de register-kleuring/ordening-staart (community-tool decomp-permuter).
- **m2c semantic drafts**: voor grote scaffold-loze functies (0x400+), als comprehension-hulp.

## Cross-game specifiek (wij, niet sm64ds)
- Ons corpus is MEERDERE games (st + pokediamond + sm64ds + khdays...), zelfde compiler 1.2.
- SDK-laag: tools/sdk_import.py (byte-import) + tools/nametransfer.py (namen) +
  agent-ombouw van ai/sdk_nearhits.json (80-98% bijna-treffers).
- Naam-transfers zijn HYPOTHESES (families delen namen); orakel bevestigt de definitieve naam.

## Zelf-verificatie-loop (verplicht na elke wijziging)
Deze drie tools vormen de snelle feedback-loop die vals-positieven en naam-drift
onmogelijk maakt. Draai ze; vertrouw nooit een build zonder.

1. `tools/doctor.py` (0,2s, geen build) — consistentie-preflight. Vangt VOORAF:
   - NAAM-DRIFT: een src/*.c definieert een andere naam dan het config-symbool.
   - ORPHAN-REF: een `extern` verwijst naar een niet-bestaand symbool (link-undefined).
   - STALE-GUARDS: build.sh mist de `rm mkds_eur.nds` / hard-fail-bescherming.
   - dubbele adressen / missende scratch / dekkingscijfer.
   Draait automatisch als stap [0/6] van build.sh; een rode doctor stopt de build.
2. `bash build.sh` — bouwt met object-cache (warm ~10s), WIST de oude ROM vooraf en
   FAALT HARD bij een link-fout. Een SHA-match hier is dus echt bewijs, geen stale ROM.
3. `tools/diffmap.py` — alleen bij VERSCHIL: wijst de afwijkende bytes toe aan de
   schuldige TU('s), classificeert (layout-shift = grootte-bug / inhoud = reloc-bug /
   gap = verschoven call-doel). `--quarantine` parkeert de eerste-orde-boosdoeners.

REGEL: een "byte-perfect" claim is alleen geldig na een SCHONE build.sh (die de ROM
vooraf wist en hard faalt) + groene doctor. Nooit een oude mkds_eur.nds vertrouwen.

## Naamgeving loopt mee met matchen
Zodra coddog_pool.py een familie matcht, roept het automatisch names.compute() aan en
werkt ai/names.jsonl bij (bewijs + naam-voorstellen) — geen aparte naam-ronde meer.
- tools/names.py --record : alleen het grootboek bijwerken (geen code-wijziging).
- tools/names.py --apply  : HOOG-zekerheid (unieke asset-string) hernoemen naar
  Maybe_<asset> + MIDDEL/LAAG annoteren met // bewijs:-comment. Bytes blijven gelijk
  (relocs gebruiken adressen; namen raken geen bytes).
- hangin.py injecteert de // bewijs:-comments uit het grootboek bij elke generate,
  zodat ze een src/-regeneratie overleven.
REGEL: verzin nooit een zekere naam uit onvoldoende bewijs. Maybe_-prefix = vermoeden.

## Kennisbank (zelf-lerend, agents lezen ÉN schrijven)
- ai/tricks.jsonl  : codegen-trucs {truc, wanneer, bron}. wave_prep injecteert de
  volledige lijst in elke briefing; agents MOETEN nieuwe beslissende trucs zelf
  appenden. Dit vervangt mij (hoofd-agent) als handmatige, verlieslatende kopieerder.
- ai/structs.jsonl : afgeleide structs per GLOBAL-adres {global, naam, size, def, bron}.
  wave_prep injecteert bekende structs als een doel-functie die globals raakt
  ("NIET opnieuw afleiden"); agents appenden nieuw afgeleide structs.
- Regel: dit zijn de enige twee gedeelde bestanden die een wave-agent mag aanraken
  (naast zijn eigen scratch). Harvest/doctor verifiëren als vanouds — de kennisbank
  beïnvloedt nooit bytes, alleen snelheid en slaagkans.
FALEN-LESSEN: rapporteer ook wat NIET werkte als truc-regel met "werkt NIET:"-prefix.
- ai/funcfacts.jsonl : per gematchte functie {sig, doc} — automatisch geoogst uit
  onze eigen src/ (tools/funcfacts.py). wave_prep injecteert de EXACTE signaturen
  + samenvattingen van al-gematchte callees in elke briefing: agents hoeven
  arg-aantallen/returnwaarden van bekende functies nooit meer te raden.
  Draai tools/funcfacts.py na elke harvest (of laat harvest het doen).
