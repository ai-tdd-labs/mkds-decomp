// PURPOSE: Checks whether a mission stage has been beaten.
// The two inputs probably identify the mission level and stage.
// The helper probably writes its status and beaten value into a small result.

typedef unsigned char u8;

extern void GetMissionLevelStageInfoByIds_from_thumb(int levelId, int stageId, u8 *result);

int IsMissionStageBeaten(int levelId, int stageId, int *beaten)
{
    u8 result[2];
    int isBeaten = 0;

    GetMissionLevelStageInfoByIds_from_thumb(levelId, stageId, result);
    if (result[0] == 1) {
        *beaten = result[1]; // The helper returned a valid stage record.
        isBeaten = 1;
    }
    return isBeaten;
}
