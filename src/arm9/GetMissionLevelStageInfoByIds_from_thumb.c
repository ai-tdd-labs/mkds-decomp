// PURPOSE: Gets mission stage information from its numeric IDs.
// The first two one-based IDs select a small stage record in the current mission data.
// The third argument receives the information copied from that record.

typedef unsigned char u8;

typedef struct MissionStageInfo {
    u8 pad_00[4];
    u8 records[];
} MissionStageInfo;

typedef struct MissionContext {
    u8 pad_00[0x10];
    MissionStageInfo *stageInfo;
} MissionContext;

extern MissionContext *data_0217aa08;

extern unsigned int GetMissionLevelStageInfo_from_thumb(void *source,
                                                         void *destination);

int GetMissionLevelStageInfoByIds_from_thumb(int levelId, int stageId,
                                              void *destination)
{
    GetMissionLevelStageInfo_from_thumb(
        &data_0217aa08->stageInfo->records[(levelId - 1) * 9 + stageId - 1],
        destination);
    return 1;
}
