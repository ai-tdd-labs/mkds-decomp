// PURPOSE: Checks whether every mission has a star-rank clear.
// It first confirms that the active mission selection is within the normal range.
// Every stage except the active one probably needs a recorded rank from five to seven.
// The active stage must not already have such a rank.

extern int GetCurrentMissionLevel(void);
extern int GetCurrentMissionLevelStage(void);
extern int IsMissionStageBeaten(int level, int stage, int *value);

#pragma optimize_for_size on

int MaybeAllMissionStagesBeatenWithStarRank_from_thumb(void)
{
    int level;
    int stage;
    int beaten;
    int value;

    if (GetCurrentMissionLevel() < 1 ||
        GetCurrentMissionLevel() > 6 ||
        GetCurrentMissionLevelStage() < 1 ||
        GetCurrentMissionLevelStage() > 9) {
        return 0;
    }

    for (level = 1; level <= 6; level++) {
        for (stage = 1; stage <= 9; stage++) {
            beaten = IsMissionStageBeaten(level, stage, &value);
            if (level == GetCurrentMissionLevel() &&
                stage == GetCurrentMissionLevelStage()) {
                if (beaten == 0) {
                    continue;
                }
                if ((unsigned int)(value - 5) <= 2) {
                    return 0;
                }
                continue;
            }
            if (beaten != 0) {
                if (value == 5 || value == 6 || value == 7) {
                    continue;
                }
                goto rank_failure;
            }
            goto not_beaten_failure;

        rank_failure:
            return 0;
        not_beaten_failure:
            return 0;
        }
    }
    return 1;
}
