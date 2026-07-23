/*
 * PURPOSE: Runs a cleanup step only for the race modes that need it.
 *
 * Reads the global race configuration (gRaceConfig). If raceMode is 2 and
 * the extra flag at offset 0x18 is zero, it calls the cleanup helper and
 * returns its result immediately. Otherwise, if raceMode is not 4 it
 * returns 0 without doing anything; if raceMode is 4 it calls the cleanup
 * helper and returns its result.
 */

typedef struct RaceConfig {
    int field0;      /* 0x0: 1-based index (klasse/cup-blok) */
    int field4;
    int raceMode;    /* 0x8: race mode selector */
    int fieldC;
    int field10;     /* 0x10: second index (probably course number) */
    int field14;     /* 0x14: sub-variant */
    int field18;     /* 0x18: extra flag checked here */
} RaceConfig;

extern RaceConfig *gRaceConfig;

extern int func_0209bf8c(void);

int func_020a3f48(void) {
    RaceConfig *cfg = gRaceConfig;
    int mode = cfg->raceMode;

    if (mode == 2 && cfg->field18 == 0) {
        return func_0209bf8c();
    }

    if (mode != 4) {
        return 0;
    }

    return func_0209bf8c();
}
