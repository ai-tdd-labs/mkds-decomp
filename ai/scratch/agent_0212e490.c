/*
PURPOSE: Gets the data pointer for a sound wave archive.
The wave archive ID selects its information entry.
Flags probably request loaded data, with one entry flag selecting a special loader.
If supplied, the output pointer receives the resulting wave data.
*/

typedef unsigned int u32;

typedef struct SoundSwarInfoEntry {
    u32 fileId : 24;
    u32 flags : 8;
} SoundSwarInfoEntry;

extern SoundSwarInfoEntry *Sound_GetSwarInfoEntry(int waveArchiveId);
extern void *Sound_PrepareSwarDataImpl(u32 fileId, void *heap,
                                       int preparationOption);
extern void *Sound_PrepareSwarData(u32 fileId, void *heap,
                                   int preparationOption);
extern void *Sound_MaybeGetRawFilePointer(u32 fileId);

int Sound_GetSwarPointer(int waveArchiveId, u32 flags, void *heap,
                         int preparationOption, void **waveDataOut)
{
    SoundSwarInfoEntry *waveInfo;
    void *waveData;

    waveInfo = Sound_GetSwarInfoEntry(waveArchiveId);
    if (waveInfo == 0) {
        return 5;
    }

    if (flags & 4) {
        if (waveInfo->flags & 1) {
            waveData = Sound_PrepareSwarDataImpl(
                waveInfo->fileId, heap, preparationOption);
        } else {
            waveData = Sound_PrepareSwarData(
                waveInfo->fileId, heap, preparationOption);
        }
        if (waveData == 0) {
            return 9;
        }
    } else {
        waveData = Sound_MaybeGetRawFilePointer(waveInfo->fileId);
    }

    if (waveDataOut != 0) {
        *waveDataOut = waveData;
    }
    return 0;
}
