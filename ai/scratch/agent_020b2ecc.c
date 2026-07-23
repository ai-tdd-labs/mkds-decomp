// PURPOSE: Checks whether the current mission stage counts as cleared.
// Reads the active mission and stage and asks the mission-progress system.
// It probably only returns true for stages five through seven while the menu is active.

#pragma optimize_for_size on

typedef struct MissionMenuState {
    char padding[0x20];
    int field_20;
} MissionMenuState;

extern int GetCurrentMissionLevel_0(void);
extern int GetCurrentMissionLevelStage_0(void);
extern int IsMissionStageBeaten(int level, int stage, int *value);
extern int func_020b2d54(void);
extern MissionMenuState *data_0217b354;

int func_020b2ecc(void)
{
    int stageValue;
    int beaten;

    beaten = IsMissionStageBeaten(GetCurrentMissionLevel_0(),
                                  GetCurrentMissionLevelStage_0(),
                                  &stageValue);
    if (func_020b2d54() == 0 &&
        data_0217b354->field_20 != 0 &&
        beaten != 0 &&
        (unsigned int)(stageValue - 5) <= 2) {
        return 1;
    }
    return 0;
}
