/* PURPOSE: Looks up the kart AI settings for the current race and remembers where they are.
 *
 * No arguments. Clears the global "current kart AI params" pointer
 * (data_0217aec0), then bails out for scenes that have no AI racing
 * (sceneId 5, sceneId 6 = staff roll, or raceMode 2). Otherwise it finds
 * the file buffer of "kartAIparam.bin" and points data_0217aec0 at the
 * 12-byte parameter entry for the current race:
 *  - raceMode 0 (probably Grand Prix): entry index = unk10 + 12*(unk0-1)
 *    (probably course-within-cup + 12 courses per class block).
 *  - other modes: index = 12*(unk0-1) + 3*(unk10+1), then +1 entry if
 *    unk14 == 2 or +2 entries if unk14 == 3 (probably a difficulty/cc
 *    sub-variant). Field meanings are guesses; the math is exact.
 */

typedef unsigned char u8;

/* Partial view of the race config (ptr at 0x021759c0). Known fields from
 * ai/structs.jsonl: 0x8 raceMode, 0xc sceneId (6 = staff roll). Offsets
 * 0x0/0x10/0x14 are used as plain ints here. */
typedef struct RaceConfig_02085fd8 {
    int unk0;     /* 0x00: 1-based index (class/cup block) */
    int unk4;     /* 0x04 */
    int raceMode; /* 0x08: 2 = skip AI params */
    int sceneId;  /* 0x0c: 5/6 = skip (6 = staff roll) */
    int unk10;    /* 0x10: second index (probably course number) */
    int unk14;    /* 0x14: 2 -> +1 entry, 3 -> +2 entries */
} RaceConfig_02085fd8;

extern RaceConfig_02085fd8 *gRaceConfig; /* race config pointer */
extern u8 *data_0217aec0;                  /* -> current 12-byte kart AI entry */
extern char data_02165990[];               /* "kartAIparam.bin" */
extern u8 *FindFileBufferGeneric_KME_KM1_KM2_KSB_from_thumb(char *name);

void MaybeLoadKartAIData_from_thumb(void)
{
    RaceConfig_02085fd8 *c;
    u8 *buf;
    u8 *p;
    int scene;

    data_0217aec0 = 0;
    c = gRaceConfig;
    scene = c->sceneId;
    if (scene == 5)
        return;
    if (c->raceMode == 2)
        return;
    if (scene == 6)
        return;

    buf = FindFileBufferGeneric_KME_KM1_KM2_KSB_from_thumb(data_02165990);
    c = gRaceConfig; /* reload through the global after the call */
    if (c->raceMode == 0) {
        /* entry = unk10 + 12*(unk0-1), each entry 12 bytes */
        p = buf + (c->unk10 + (c->unk0 - 1) * 12) * 12;
    } else {
        p = buf + ((c->unk0 - 1) * 12 + (c->unk10 + 1) * 3) * 12;
        /* two-case dispatch as switch: beq-chain with predicated adds */
        switch (c->unk14) {
        case 2:
            p += 0xc;
            break;
        case 3:
            p += 0x18;
            break;
        }
    }
    data_0217aec0 = p;
}
