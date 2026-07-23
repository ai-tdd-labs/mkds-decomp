/*
 * PURPOSE: Decides whether the race can proceed, checking the AI-kart data
 *          load first when the current race mode needs it.
 *
 * Reads the active race mode from gRaceConfig. For time-trial-like modes
 * (mode 3 or 5) it first makes sure the kart AI data finished loading
 * (func_02061818); if that check fails the function bails out with 0.
 * Otherwise (and for any other mode) it defers to func_0209bf8c, whose
 * return value becomes this function's result.
 */

typedef struct RaceConfig {
    int field_0;
    int field_4;
    int mode; /* offset 8: race mode/type selector */
} RaceConfig;

extern RaceConfig *gRaceConfig;
extern int func_02061818(void);
extern int func_0209bf8c(void);

int func_02094e3c(void)
{
    int mode = gRaceConfig->mode;

    if (mode == 3 || mode == 5) {
        if (func_02061818() == 0) {
            return 0;
        }
    }

    return func_0209bf8c();
}
