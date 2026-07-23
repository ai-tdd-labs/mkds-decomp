/*
 * PURPOSE: Runs a helper when the race is in mode 2 with the extra flag set.
 *
 * Reads the global race configuration (gRaceConfig). If raceMode is 2 and
 * the extra flag at offset 0x18 is 1, it calls the helper and returns its
 * result. Otherwise it returns 0.
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

int func_020a6d40(void) {
    RaceConfig *cfg = gRaceConfig;

    if (cfg->raceMode == 2 && cfg->field18 == 1) {
        return func_0209bf8c();
    }

    return 0;
}
