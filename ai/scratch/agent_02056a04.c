// PURPOSE: Sets mission stage information from its numeric IDs.
// The first two one-based IDs select a small stage record in the current mission data.
// The third argument supplies the information copied into that record.

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

extern void SetMissionLevelStageInfo_from_thumb(void *destination, const void *source);

void SetMissionLevelStageInfoFromIds_from_thumb(int levelId, int stageId,
                                                 const void *source)
{
    SetMissionLevelStageInfo_from_thumb(
        &data_0217aa08->stageInfo->records[(levelId - 1) * 9 + stageId - 1],
        source);
}
