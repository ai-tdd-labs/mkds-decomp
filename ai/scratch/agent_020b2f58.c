// PURPOSE: Checks whether the current mission is boss six or boss seven.
#pragma optimize_for_size on

extern int GetCurrentMissionLevel_0(void);
extern int GetCurrentMissionLevelStage_0(void);

int IsCurrentMission_Boss6OrBoss7_from_thumb(void)
{
    if (GetCurrentMissionLevel_0() == 6) {
        if (GetCurrentMissionLevelStage_0() == 9) {
            goto success;
        }
    }

    if (GetCurrentMissionLevel_0() != 7) {
        goto failure;
    }
    if (GetCurrentMissionLevelStage_0() != 9) {
        goto failure;
    }

success:
    return 1;

failure:
    return 0;
}
