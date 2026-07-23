// PURPOSE: Checks whether the current race scene is normal or replay.
// The function probably accepts only scene 2 and then checks the active race
// configuration's variant field. It returns one for normal or replay variants.

#pragma optimize_for_size on

typedef struct RaceConfig_02105504 {
    char padding_00[0xc];
    int variant;
} RaceConfig_02105504;

extern int GetCurrentSceneId(void);
extern RaceConfig_02105504 *gRaceConfig;

int IsInRaceSceneNormalOrReplay(void) {
    int result = 0;

    if (GetCurrentSceneId() == 2) {
        int allowed = 1;
        int variant = gRaceConfig->variant;

        if (variant != 0) {
            if (variant != 2) {
                allowed = result;
            }
        }
        if (allowed != 0) {
            result = 1;
        }
    }
    return result;
}
