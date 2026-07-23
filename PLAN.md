# MKDS greenfield AI-decomp — draaiboek

Doel: matching decomp van Mario Kart DS (~5.000 functies) met de st/sm64ds-pipeline.

## Benodigd van Chris
- Eigen cartridge-dump: **Mario Kart DS (Europe)** (.nds, No-Intro) → `extract/baserom_mkds_eur.nds`
  (EU/AMCP omdat mkds-re-symbolen én de decomp-headers EU-adressen gebruiken)

## Stappen (volgende sessie)
1. `dsd rom extract` + `dsd init` → genereert config/ (symbols, delinks, relocs skelet)
2. Compiler pinnen: MKDS is nov 2005 → sweep mwccarm 1.2/2.0-serie (zit al in st/tools/mwccarm)
   over een kleine leaf-functie tot byte-match; vlaggen raden via SDK-conventies (-O4,p etc.)
3. Symbolen importeren: mkds-re/re-export/mkds-eu-symbols.x (7.105 syms, 4.958 functies)
   → converteren naar dsd symbols.txt-formaat
4. Structs: mkds-decomp-headers/ (195 headers van Gericom & Ermelber) als include/-basis
5. SDK-functies gratis matchen via `dsd sig` (NitroSDK-signatures)
6. aimatch/aiworklist/aicoddog kopiëren vanuit st/tools + paden aanpassen
7. Proof of concept: 1 kleine functie byte-matchen; daarna batches zoals bij st

## Referenties op schijf
- ../st (werkende pipeline + notes), ../sm64ds-decomp (methodiek), 
- ../mkds-re (symbolen), ../mkds-decomp-headers (structs)

## Status 2026-07-14
- ✅ USA-ROM (AMCE rev0, ontsleuteld) uitgepakt: arm9 1,47 MB + ITCM/DTCM + 4 overlays
- ✅ `dsd init` geslaagd (met --allow-unknown-function-calls; 2 unknown-functies, benign)
- ✅ `dsd delink` draait → baseline-objecten in build/usa/delinks
- **Geteld: 7.991 functies** (arm9 7.695 + itcm 101 + ov000/1/3 195)
- Let op: symbolen/headers zijn EU; port naar USA via byte-similarity (coddog-aanpak) is de klus
- Volgende: compiler pinnen (sweep 1.2/2.0-serie op leaf-functie), aimatch/aiworklist kopiëren,
  eerste byte-match als PoC

## Status EU (2026-07-14, later)
- ✅ EU-ROM (AMCP rev0) geverifieerd, uitgepakt, `dsd init` OK → config/eur (7.991 functies)
- ✅ IDA-symbolenimport: 2.317 functies hernoemd naar echte namen (100% adres-alignment!),
  delink blijft groen. Voorbeelden: GetDriverPlace, NotifyDriverFinished, VerifySelectKartFiles.
- EU is nu de primaire versie; USA-config blijft staan als secundair.
- Volgende: compiler pinnen (sweep loopt), SDK-import-pass, headers koppelen, tools kopiëren.

## COMPILER GEPIND (2026-07-14): mwccarm 1.2 (base/sp2p3/sp3-trio)
- Bewijs: relatieve divergentie-sweep over 45 SDK-functies. 1.2-trio geeft overal laagste div;
  2.0-serie structureel hoger (FX_DivAsync 1→18, OS_JamMessage 27→45, SND 3→19).
- Scheidsrechter MTX_Concat43: div13 bij 1.2/base·sp2p3·sp3, div225 bij sp4 én 2.0 → sluit sp4+2.0 uit.
- = exact de sm64ds-compiler (1.2/sp2p3). sm64ds-corpus (10.216 bronnen) dus byte-compatibel.
- Werkversie: 1.2/sp2p3. Restdiv op SDK-functies = bronverschil (pokediamond SDK 2006 vs MKDS 2005),
  niet compiler. Definitieve subversie-pin volgt zodra 1e echte game-functie matcht.
- Vlaggen nog te bepalen (sm64ds gebruikt: -O4,p -enum int -lang c99 -char signed -interworking
  -proc arm946e -gccext,on); testen op 1e match.

## EERSTE MATCHES (2026-07-14): 7/7 byte-identiek! Compiler-pin bevestigd.
- Toolchain werkt: tools/aimatch.py (mwccarm 1.2/sp2p3 via wine, byte-diff tegen MKDS-binary).
- Gematcht: Os_Thread_GetPriority, Os_IsEmulator, Os_Lock_GetOwnerId, Os_Thread_IsTerminated,
  SetCardOwnerArm9, Os_SetMemoryRegionStartAddress, Fs_OverlayInfo_GetBinarySize.
- Les: `(x<<8)>>8` optimaliseert weg naar bic; 24-bit bitfield lezen forceert de lsl/lsr-shifts.
- Dit BEWIJST dat 1.2/sp2p3 correct is (verkeerde compiler = geen match). MKDS 0% -> eerste echte matches.
- Nog te doen: buildsysteem (configure+ninja) voor de volledige ROM-SHA1-proef; SDK-import-pass;
  headers koppelen; dan batch/fan-out.

## Getimede batch (2026-07-14): compile+verify-tijden
- Elke compile+verifieer-cyclus op wine: 2-4 s.
- Simpele functie (getter/setter/flag): 1 poging, ~1 min incl. lezen+schrijven.
- Middel (struct-init, guard-keten): 2-3 pogingen, ~2-4 min. Meestal 1 iteratie voor struct-offset.
- Near-miss: Crt0_MemorySet32 — hand-geoptimaliseerd stmlt-fill-lus-idioom, niet uit C te forceren.
- Totaal deze sessie: 9 byte-matches + 1 near-miss.

## Multi-decomp harvest + cross-game (2026-07-14 avond)
- ALLE 14 bekende NDS-decomps gecloned en geoogst (pokediamond/platinum/heartgold, pmd-sky,
  khdays, twewy, ph, st, nsmb, sm64ds, ooe, dqiv, fe11, rhgold; dqiv/fe11/rhgold hadden geen libs).
- SDK-bulk-laag VERZADIGD op ~180 byte-identieke functies (11,3 KB); nieuwe repos voegden niets
  toe (zelfde SDK-revisies). Grootste vangst: __ieee754_pow 4660 B. IDA-naam "CheckZetaInvokeBeta"
  gecorrigeerd naar `exit`.
- tools/crossgame.py: MKDS-functies gerankt tegen st-corpus (mnemonic-similarity). Honderden
  kandidaten 60-91%. PoC: memchr omgebouwd van st-bron -> byte-match in 2 pogingen.
- NIEUWE LES: MSL memchr gebruikt word-load + and 0xff (byte-extract-idioom): `*(const u32 *)p & 0xff`.
- Volgende: 180 registreren in config, cross-game batch met agents (workflow = ranking ->
  bron ombouwen -> aimatch), GX-disambiguatie, buildsysteem.

## sm64ds-methodiek overgenomen (2026-07-14 laat)
- notes/: mwccarm-codegen.md (920r), pret-idioms.md, matching-style.md, actor-naming.md,
  link-verification.md — geimporteerd uit sm64ds (MIT, tangosdev), met attributie.
  Idiomen transfereren (zelfde compiler 1.2); elke les tegen MKDS verifieren.
- AGENTS.md: operationele regels (model-routing Sonnet-default/Fable-mid-band/Opus->Fable,
  worklist-per-batch, dry-run banken, vroege stop, notes minen, two-stage retry, floor-lijst).
- tools/clone.py: gratis clone+paramclone post-pass (werkt; yield groeit met corpus).
- NOG TE BOUWEN (sm64ds heeft ze): linkcheck (WRONG-DEST-gate), permuter (kleuring-staart),
  m2c drafts (grote functies), crackloop-orchestratie (1-commando batch).
- Modelles: agents voortaan Sonnet-default; Fable(high) voor mid-band vormmuur; niet Opus-voor-alles.

## Tooling gebouwd (2026-07-14, 'nog te bouwen'-lijst)
- tools/linkcheck.py: WERKT. WRONG-DEST-poort — verifieert reloc-doelen tegen config
  (16k symbolen, 47k relocs). Getest: SND_GetWaveDataAddress -> LINK OK (2 doelen).
  Gebruik NA elke match voordat je landt/PR't.
- tools/clone.py: WERKT. Gratis clone+paramclone-pass. Yield nu laag (corpus 178, vnl. uniek);
  groeit sterk zodra game-functie-families landen.
- tools/permute.py: HARNESS werkt (compileert/scoort/houdt beste), maar mutatieset te dun
  (alleen decl-reorder, herkent aangepaste types nog niet). Voor echte kleuring-muur:
  externe decomp-permuter clonen OF Fable-tier handwerk (sm64ds' gemeten oplossing).
- NOG open: m2c drafts (externe tool matt-kempster/m2c clonen), crackloop-orchestratie (glue).

## Family-finder gebouwd (tools/families.py) — het TEQSub-effect gesystematiseerd
- 5.873 ongematchte functies geclusterd op instructie-skelet (immediates genormaliseerd).
- **128 families (>=3 leden) = 712 functies = 12% van de band** in ai/families.json.
- Top: 34x 28B-patroon, 23x 116B, 16x LoadXxxMapObject-laders (gamecode!), 16x CopyBgData_*.
- Nieuwe batch-strategie: 1 agent per FAMILIE (niet per functie) — gemeten 8-voudige opbrengst
  bij TEQSub. 128 agent-taken ~ 712 potentiele matches.
- Volgende tools op de ladder: batch-ledger + notes-miner, diff-verklaarder, struct-inferencer,
  melonDS-GDB-tracer (dynamische oracle voor semantiek/floor-validatie).

## Fase A voortgang (2026-07-14, na herstart) — families draaien
- Family-finder + register_batch (auto-ledger) + linkcheck-fix (thumb-bit false-positive) gebouwd.
- 10 families gekraakt, ALLE 100%: FAM0(12) FAM2(12) FAM3-MapObjLoaders(12) FAM4(12)
  CopyBgData(12) IDX1-thunks(12) IDX6-alloctramp(12) GXS-window(11) ModelBlock(11) RacerGetters(11).
- Subsystemen blootgelegd: map-object-machinerie (laders/thunks/billboards/allocators rond 0x2099),
  racer-datastruct (data_0217561c stride 0x8c: charId@0x68 name@0x88 kartId@0x6c team@0x74 type@0x70),
  3D-materiaal-setters, scherm-BG-copy.
- Register 123 + 180 SDK-import = ~303 uniek byte-geverifieerd (~3.8%). Gem ~26s/functie, hit 100%.
- Agents leggen ZELF lessen vast (unsigned-loopteller-regel) en registreren zichzelf -> lerend systeem.
- GXS-familie: naam-transfer GXS_SetGraphicsMode bleek FOUT (echt: window/BG-display-flags);
  namen nog corrigeren. Naam-transfers blijven hypothese tot agent-verificatie.

## Fase B (buildsysteem) — pijplijn af, basislijn geblokkeerd door MKDS-quirks
- build.sh: dsd delink -> lcf -> mwldarm link (-m Entry) -> dsd rom config/build -> sha1. WERKT end-to-end.
- Basislijn-herbouw (gap-objecten): ITCM/DTCM/ov002 100% byte-identiek (machinerie bewezen correct).
- arm9: 143 bytes af (0.010%), allemaal reloc-slots die dsd niet mapt (runtime-codegen-quirk,
  zelfde als --allow-unknown-function-calls). ov000/1/3: 8.6% af (overlay-reconstructie/compressie).
- GEVOLG: byte-perfecte ROM-SHA1 nog niet haalbaar op MKDS zonder dieper dsd-werk (mogelijk upstream-fix).
- BELANGRIJK: dit blokkeert het matchen NIET — aimatch (per-functie-oracle) blijft 100% betrouwbaar.
  De ROM-build is een assemblage-controle bovenop, geen voorwaarde voor geldige matches.
- Vervolg: dsd delink-relocatieprobleem uitzoeken (de ~143 onmapbare + overlay-compressie),
  of een objdiff-config voor per-functie-voortgang op decomp.dev (werkt zonder volledige ROM-build).

## ROM-build-diagnose VOLTOOID (2026-07-15): oorzaak exact bekend
- arm9's 143 diff-bytes = ALLEMAAL hetzelfde woord: pointer 0x021a99e1 (orig) vs 0x021a99e0
  (herbouwd) -> THUMB-BIT-VERLIES op kind:load-relocaties naar een thumb-functie.
- Doelfunctie geidentificeerd: 0x021a99e0 = thumb-functie in ov000 (push {r4,lr}...), maar in
  config als data(any) geclassificeerd EN 'ambiguous' (bestaat in ov000/ov001/ov002 = overlay-swap;
  ov001 heeft daar een string "on_run", ov002 te klein -> ov000 is bewezen de juiste).
- Config-fix geprobeerd (symbol -> function(thumb,size=0x28), 23 relocs -> module:overlay(0)):
  slechts 1 byte verbetering. CONCLUSIE: dsd emit ABS32/load-relocs naar thumb-functies zonder
  thumb-bit in de gap-objecten; fix moet in dsd zelf (Rust) of via mwldarm-symboolmarkering.
- ov000/1/3-diffs (8-9%) waarschijnlijk zelfde klasse op grotere schaal (overlay-swap ambiguiteit).
- VERVOLGOPTIES: (a) dsd-source patchen (we hadden /tmp/dsd-src; ~2-3 sessies), (b) upstream issue
  bij AetiasHax (bekende klasse, issue #58 verwant), (c) parkeren en objdiff-route voor voortgang.
- Matchen blijft 100% onaangetast (aimatch per-functie-oracle).

## DOORBRAAK (2026-07-14 avond): arm9 BYTE-PERFECT
Werkelijke oorzaakketen (eerdere thumb-bit-diagnose was omgekeerd):
1. mwldarm -interworking bepaalt thumb-heid van ABS32-doelen OP ADRES; ov000/1/2
   overlappen -> linker ziet thumb-regio van verkeerde overlay -> spurieuze +1
   (130 van 138 arm9-diffs). Origineel had ÉVEN pointers.
2. Oplossing: tools/fix_interwork.py — post-linkstap die per kind:load-reloc de
   verwachte waarde uit de dsd-config berekent (thumb-bit alleen als het opgeloste
   doel écht thumb is) en mwld's fouten patcht. 6424 slots gecorrigeerd,
   0 config-fouten, 0 onbeslisbaar.
3. Rest-6-bytes: BL vs BLX — dsd emit geen $t-mapping op JUMPTABLE-doelen na een
   pool (wel op branch-doelen). Fix: .L_020cbf74 kind:label(thumb) in symbols.txt.
   (Kandidaat voor dsd-upstream-issue: jumptable-case-labels -> mapping symbols.)
4. build.sh: rm -rf delinks voor elke delink (stale objecten = dubbele definities).
RESULTAAT: arm9.bin 0 diff-bytes. Overlays nog: lengteverschuivingen door padding
(ov000 +64 @0x30304, ov001 +96 @0x271a4, ov003 +256 @0x30) — volgende stap.

## FASE B VOLTOOID (2026-07-14): volledige ROM byte-perfect (SHA1-match, 23s build)
Na arm9 waren er nog 4 lagen; alle opgelost:
1. Overlays (veneers + spurieuze thumb-bits): dsd delink -M / --all-mapping-symbols.
   Zonder -M krijgen data-symbolen geen $d-mapping -> mwldarm's interworking-
   moduskaart heeft gaten -> 41 veneers + verkeerde +1's. Met -M: 0 veneers,
   alle modules (arm9/itcm/dtcm/ov000-003) direct 0 diff-bytes uit de linker.
   (tools/fix_interwork.py daardoor overbodig; bewaard als diagnose-tool.)
2. Overlay-tabel signed-vlag (03 vs 01): signed: true per overlay in config.yaml.
3. Multiboot-signature (136 bytes RSA na laatste file): ds-rom-detectie faalt
   omdat MKDS 'm op een niet-4-aligned offset heeft (rom_size_ds=0x1860b9e).
   Workaround: extract/eur/multiboot_signature.yaml handmatig gegenereerd.
4. Gemengde padding (0x00 na arm9-blok/ov-files, 0xff na arm7/FNT/FAT):
   ds-rom kent 1 section_padding_value. tools/fix_padding.py stempelt gap-bytes
   uit het origineel, mét uniformiteits-guard (abort als gap geen puur pad is).
   section_padding_value op 255 gezet (meeste gaps), stamper doet de rest.

UPSTREAM-KANDIDATEN (AetiasHax):
- dsd: geen hervattende $t na pools op jumptable-doelen (arm9-case 0x020cbf74);
- dsd: -M zou default (of aanbevolen) moeten zijn voor matchende builds;
- ds-rom: multiboot-detectie weigert niet-4-aligned offsets (MKDS EUR);
- ds-rom: gemengde sectie-padding niet uitdrukbaar.

Betekenis: het ROM-orakel is nu end-to-end. Elke toekomstige gematchte TU kan
via delinks.txt 'complete' in de link en de build MOET ce97d9... blijven geven.

## TU-INHANG BEWEZEN (2026-07-14): gematchte C zit ECHT in de byte-perfecte ROM
Vraag: "zitten de al-gematchte functies byte-matchend IN de rom?"
Antwoord vóór deze stap: NEE — de ROM was byte-perfect maar 100% uit dsd-gap-
objecten (originele bytes her-uitgezonden). De 161+341 matches waren per-functie
geverifieerd door het orakel (aimatch: compileer C -> vergelijk ROM-bytes,
reloc-slots gewildcard) maar zaten NIET in de build.
Nu bewezen met Os_Thread_GetPriority (leaf, geen relocs):
- src/os/thread_getprio.c toegevoegd; delinks.txt-blok met 'complete' +
  .text 0x0200dcd8..0x0200dce0; ai/tus.txt koppelt bron->objectpad.
- build.sh stap 2b compileert onze TU's NA delink (anders overschrijft de
  re-delink onze .o met dsd's referentie), lcf plaatst het, mwldarm linkt het.
- Resultaat: SHA1 blijft ce97d9... met ONZE gecompileerde C i.p.v. ROM-bytes.
Dit is de brug tussen het per-functie-orakel en de volledige ROM: elke matched
TU kan nu 'complete' de link in en de build bewaakt 'm permanent.
VOLGENDE: batch-tool die alle 161 matched.jsonl-functies TU-blokken geeft
(alleen relocvrije/leaf eerst; functies met calls hebben correcte reloc-symbolen
in de C nodig -> linkcheck-poort). Overlay-TU's idem via hun delinks.txt.

## 154/155 GEMATCHTE FUNCTIES BYTE-PERFECT IN DE ROM (2026-07-14)
tools/hangin.py hangt alle bevestigde matches als 'complete' TU's in (src/<mod>/<func>.c,
delinks-blok, ai/tus.txt) en verifieert via SHA1. Resultaat: 154 arm9-TU's linken
byte-perfect; ROM blijft ce97d9... met ONZE C i.p.v. ROM-bytes. 1 itcm-functie
(func_01ff8058, asm-reimpl) geparkeerd: verwijst naar OSi_IrqThreadQueue/OSi_ThreadInfo
die nog niet als symbool in de config staan (-> eerst die globals definiëren).

Drie valkuilen opgelost onderweg (allemaal nu in de tool/keten geborgd):
1. NAAM-SYNC (de grote): het orakel wildcardt reloc-slots, dus een match zegt niets
   over de SYMBOOLNAAM. Als onze C 'memchr' heet maar de config 'func_02134db0',
   verwijst het gap-object naar de config-naam terwijl onze TU de andere levert ->
   link stuk + layout schuift (+48 bytes bij memchr -> 194k diff). Fix:
   sync_symbol_names() hernoemt het config-symbool op elk TU-adres naar onze
   gedecompileerde naam (veilig: relocs verwijzen op adres, niet op naam). Dit is
   precies wat sm64ds doet: bestandsnaam == config-symbool.
2. STALE-OBJECT-MASKERING: bij een link-fout ging build.sh door met een oude arm9.o
   en gaf alsnog SHA-match (vals-positief, claimde '155'). Fix: rm arm9.o + hard
   exit 1 als de link faalt of 'Link failed' bevat.
3. DELINKS-HEADER-PARSING: base_delinks moet stoppen bij het eerste TU-blok, want
   TU-'.text'-regels matchen dezelfde regex als de module-layout.

Diff-gebaseerde TU-detectie (bad_by_diff) faalt bij layout-shifts (cascade); daarom
kernoorzaken direct opgelost i.p.v. via bisect. build.sh compileert TU's in stap 2b
ná de delink. Percentage-teller: 154 echte decomp-functies nu ROM-bewaakt.

## SDK-INHANG: 302 FUNCTIES BYTE-PERFECT IN DE ROM (2026-07-15)
Doel: alle gevonden functies (matched + SDK) echt in de byte-perfecte build.
De 180 SDK-treffers hadden geen los C-bestand -> tools/sdk_hangin.py:
- her-compileert de 469 donor-bronnen (via sdk_import.build_jobs),
- snijdt per gematchte functie een geïsoleerd object uit met tools/elfobj.py
  (handgemaakte ARM ELF-REL: .text + $a/$t-mapping + func-symbool + relocs),
- reloc-doelen worden uit de ORIGINELE ROM-bytes gedecodeerd (ABS32=pool-woord,
  PC24/THM_PC22=BL/BLX-instructie) en aan het MKDS-symbool daar gekoppeld.
159 SDK-objecten geëmit; 148 linken byte-perfect. Eindstand:
  154 gecompileerde C-TU's + 148 SDK-objecten = 302 functies byte-perfect,
  SHA1 ce97d9..., alle 6 modules 0 diff. 12 geparkeerd (1 itcm-asm + 11 SDK
  met reloc-doelen die niet naar een bekend MKDS-symbool wijzen, bv. __ieee754_pow
  met 136 relocs naar interne MSL-helpers).

Drie emitter/pijplijn-bugs opgelost:
1. THUMB-ALIGNMENT: thumb-functies met size%4!=0 laten 2 opvul-bytes na tot de
   volgende functie; niet-emitten gaf een -2 cascade (128910 diff!). Fix: code
   padden tot 4-grens met de echte ROM-padding, blokgrootte meeschalen.
2. RELOC-TYPE: decode_target snapte eerst alleen calls; load-relocs (adres uit
   pool) hebben het doel in het woord zelf. compile_funcs geeft nu het reloc-TYPE
   terug -> 103 met-reloc functies inhangbaar i.p.v. 3.
3. STALE-DELINKS-BLOK: generate() herschreef alleen delinks van modules mét actieve
   TU's; een module waarvan de enige TU geparkeerd werd hield z'n oude blok (ov001,
   -20 shift). Fix: alle module-delinks eerst naar kale headers.

Teller: ~302/15686 = 1,9% echt in de ROM gelinkt (was 154). Alles wat we vonden
op ~12 lastige reloc-gevallen na. elfobj.py is herbruikbaar voor toekomstige inhang.

## OPTIMALISATIE + CODDOG-BATCH (2026-07-15)
Geleerd deze sessie -> doorgevoerd:
- BOUWTIJD was de bottleneck: build.sh hercompileerde elke keer alle C-TU's (296s).
  Fix: content-hash object-cache (build/eur/objcache/, sleutel=sha1(bron)).
  Koud 296s -> warm 10s (30x). Incrementeel 1 functie toevoegen: ~15s i.p.v. 5 min.
  Dit maakt de iteratieve decomp-loop (match -> inhangen -> SHA-test) praktisch.
- CODDOG-METING: func_020db268-familie (0x50, alloc+data-copy) = zelfde skelet,
  verschilt alleen in 1 pool-woord (het gekopieerde data-adres). 10 functies via
  pool-substitutie: 2,2s/functie (orakel-verify), 9/10 direct raak. ROM-test
  (inhangen + incrementele build): 29s. Totaal 10 functies mét ROM-verificatie ~53s.
- tools/coddog_pool.py: herbruikbaar. Neemt een gematcht sjabloon, detecteert
  pool-slots (woordwaarde die als hex in de C staat), vindt siblings met identiek
  skelet, substitueert, verifieert, registreert. Familie-multiplier in 1 commando.
Stand: 171 matched (161+10 coddog); 312 byte-perfect IN de ROM (164 C + 148 SDK).

## 50+ FUNCTIES VIA CODDOG (2026-07-15): methode + generalisatie
Gevraagd: 50 functies via coddog. Geleverd: ~75, allemaal byte-perfect in de ROM.
METHODE (getrapt):
1. Survey: tools/families.py -> 120 families / 570 functies clusteren op skelet.
2. Kies grootste families (beste analyse:opbrengst). Kraak MEMBER 1 (schrijf C,
   verifieer via orakel). Dit is de enige echte analyse per skelet.
3. Repliceer met tools/coddog_pool.py: 2.0-2.2s/functie, 100% raak binnen familie.
4. Batch: alle inhangen + incrementele build (cache) + SHA.
GENERALISATIE coddog_pool.py (deze sessie):
- config-NAAM-substitutie i.p.v. alleen hex -> thunks (indirecte call via pool).
- CALL-SLOT-maskering: relatieve bl/blx-doelen worden gemaskeerd én per sibling
  uit de ROM-bytes gedecodeerd + aan het config-symbool gekoppeld -> ontsluit
  families met echte calls (LoadSnowTree1MapObject: 25 leden in 50s).
- Grens: families die in IMMEDIATES variëren (bv. getter met #0x89c) vangt hij
  niet (eist exacte niet-slot-bytes) -> volgende tool: immediate-substitutie.
Sjablonen gekraakt: func_02099c2c/func_020ca54c (thunks), func_020b1cf4 (getter),
LoadSnowTree1MapObject (alloc+2 calls). Stand: 377 functies byte-perfect in ROM.

## CORRECTIE (2026-07-15): naam-sync-drift + stale-ROM-maskering opgelost
Ontdekt bij verificatie: de eerdere "coddog byte-perfect" was een STALE-BESTAND
vals-positief. De link faalde eigenlijk, maar een oude mkds_eur.nds (van de 302-
build) bleef staan -> SHA matchte alsnog. Twee echte bugs:
1. NAAM-SYNC-DRIFT: coddog_pool noemde matches eerst func_<addr>; hangin's
   sync_symbol_names hernoemde daarop het config-symbool (bv. LoadBankEgg1MapObject
   -> func_02099440) PERSISTENT. Een oude family-batch-functie die dat symbool als
   callback doorgeeft verwees toen naar een verdwenen naam -> link-undefined.
   Fixes: (a) coddog_pool gebruikt de CONFIG-naam (names.get(addr)); (b) sync-GUARD:
   nooit een betekenisvolle naam overschrijven met generieke func_/data_<addr>.
2. STALE-ROM: build.sh wist nu 'mkds_eur.nds' aan het begin -> een gefaalde link
   kan geen oude ROM als "SHA-match" voorspiegelen.
Herstel: config + matched.jsonl teruggezet naar de 302-baseline (0b82d32), coddog
schoon opnieuw gedraaid. ECHTE stand nu: 379 functies byte-perfect in de ROM
(231 C + 148 SDK), clean build (rm + hard-fail) = ce97d9..., arm9 0 diff.
LES: een SHA-match is alleen bewijs als de build hard faalt bij fouten én de
output-ROM eerst gewist wordt. Anders bewijst 'ie niks.

## STRATEGIE (2026-07-15): repliceerbare laag leegtrekken via parallelle agents
Expert-lezing: eerst de goedkope repliceerbare laag volledig oogsten (vliegwiel),
dan pas de echte algoritmes. Meting NA deze sessie: 116 families / 508 functies
(10% van de band) liggen nog klaar; ~5 gedaan. Bottleneck = 1 analyse per familie
(member 1 kraken) -> perfect parallelliseerbaar met subagents (sm64ds-manier).
PLAN: per golf ~6 agents, elk kraakt één familie-sjabloon (byte-match via aimatch);
coddog_pool.py repliceert elke familie in seconden; doctor+build+diffmap verifieert.
Herhaal tot families leeg; verwacht ~10-12% dekking. Daarna: immediate-bewuste
coddog voor families die in immediates variëren; dan subsystemen + dynamische oracle
voor de unieke algoritmes.
Golf 1 (loopt): func_02028d9c, GXS_SetGraphicsMode, func_020cccd8, func_020db1b0,
DisplayConfig_SetBottomEngineBg3Config_0, func_02028794.

## AUTONOME GOLF-PIJPLIJN + RONDE 1 (2026-07-15)
tools/wave_prep.py (doelselectie op contextscore + volledige agent-briefings) en
tools/wave_harvest.py (verify orakel+linkcheck, registreer, repliceer, build,
commit-bij-byte-perfect). Ronde 1: 6 agents, allen match=True (1e poging);
+26 replicaties (3-arg-thunkfamilie). Lessen/fixes:
- STRING-LITERALS: agent gaf "PakkunBody.nsbmd" letterlijk door -> nieuwe lokale
  string -> link-breuk. linkcheck vangt het (WRONG-DEST '@14'). Fix in briefing:
  strings ALTIJD via data_<adres>-symbool. 2 gevallen gerepareerd.
- -dead VERWIJDERD uit build.sh: in een volledige-reconstructie-link hoort
  deadstrip niets te doen; het strippte een TU zonder inkomende relocs. Zonder
  -dead is de build verder byte-identiek.
- OPEN MYSTERIE (geparkeerd): mwldarm weigert LogThrowAssertion.o(.text) te
  plaatsen — object is byte-schoon, lcf-regel byte-identiek aan werkende regels,
  naam-hernoeming en elfobj-heremissie veranderen niets; enige overgebleven TU
  met dit gedrag. In quarantaine (0x0213442c); match blijft geregistreerd.

## RONDE 2 + THUMB-TANDPIJN (2026-07-15)
Ronde 2 (6 agents, incl. eerste thumb-doelen): 5 byte-perfect gecommit
(FormatRaceCarcWithLanguage/thumb!, LoadTownMonte, LoadFlipper, burner,
FaceAnimationPath). Twee TOOLBUGS gevonden door de eerste thumb-golf:
1. aimatch reloc-wildcard was ARM-gealigneerd (&~3): thumb-calls op offset%4==2
   wildcardden het verkeerde halfwoord -> vals-negatief. Fix: &~1. (Gevonden en
   bewezen door de agent zelf, incl. hersimulatie.)
2. linkcheck compileerde altijd ARM (geen -thumb) -> vals WRONG-DEST op thumb-
   functies. Fix: mode uit config, -thumb bij compilatie.
LES: elke poort die compileert of offsets rekent moet mode-bewust zijn; de eerste
thumb-functie door de keten vindt ze allemaal.

## ONTDEKKING (2026-07-16): MKDS mixt compilerversies per TU
Arc_MountArchive (564B, geneste switches+recursie) kan met sp2p3 PRINCIPIEEL niet
matchen: de thumb-jumptable-dispatch verschilt (sp2p3: 'add pc,r0'; ROM: 1.2/base-
vorm 'ldrh/lsls/asrs/add pc/bx' met oneven entries). Agent bewees het via flag- en
versie-sweep; onze aimatch bevestigde: sp2p3 183/282 mis, 1.2/base 0/282 MATCH.
De jumptable-vorm is een COMPILER-VINGERAFDRUK (staat nu in tricks.jsonl).
Toolchain nu multi-versie: aimatch --mwcc, matched.jsonl 'mwcc'-veld, tus.txt
4e kolom, batch_compile groepeert per (mode,versie) + versie in cache-sleutel.
Regio-hypothese: arc/filesystem-cluster (0x2047xxx-0x2048xxx) is 1.2/base.
