// PURPOSE: Loads the requested sound sequence and banks into a resource-ID record.

typedef struct SoundResourceIds {
    int sequenceId;
    int bankId1;
    int bankId2;
} SoundResourceIds;

extern void *data_0217d130;

extern int CheckMaybeLoadSseqOk(int sequenceId, int archiveId);
extern int Sound_LoadSbnk(void *bankId, void *archiveId);

int func_0210e33c(SoundResourceIds *result, int sequenceId, int bankId1, int bankId2)
{
    if (sequenceId != 0xff) {
        if (CheckMaybeLoadSseqOk(sequenceId, data_0217d130) == 0) {
            return 0;
        }
    }

    if (bankId1 != 0xff) {
        if (Sound_LoadSbnk((void *)bankId1, data_0217d130) == 0) {
            return 0;
        }
    }

    if (bankId2 != 0xff) {
        if (Sound_LoadSbnk((void *)bankId2, data_0217d130) == 0) {
            return 0;
        }
    }

    *result = *(SoundResourceIds *)&sequenceId;
    return 1;
}
