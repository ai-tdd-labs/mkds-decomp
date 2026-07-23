/*
PURPOSE: Gets the data pointer for a sound archive.
The archive ID selects an entry, and flag bit 3 probably requests prepared data.
The heap and preparation option are used only when preparation is requested.
If the output pointer is not null, the resulting archive pointer is stored there.
*/

typedef unsigned int u32;

typedef struct SoundSarcInfoEntry {
    u32 fileId;
} SoundSarcInfoEntry;

extern SoundSarcInfoEntry *Sound_GetSarcInfoEntry(int archiveId);
extern void *Sound_PrepareSarcData(u32 fileId, void *heap,
                                   int preparationOption);
extern void *Sound_MaybeGetRawFilePointer(u32 fileId);

int Sound_GetSarcPointer(int archiveId, u32 flags, void *heap,
                         int preparationOption, void **archiveDataOut)
{
    SoundSarcInfoEntry *archiveInfo;
    void *archiveData;

    archiveInfo = Sound_GetSarcInfoEntry(archiveId);
    if (archiveInfo == 0) {
        return 3;
    }

    if (flags & 8) {
        archiveData = Sound_PrepareSarcData(
            archiveInfo->fileId, heap, preparationOption);
        if (archiveData == 0) {
            return 7;
        }
    } else {
        archiveData = Sound_MaybeGetRawFilePointer(archiveInfo->fileId);
    }

    if (archiveDataOut != 0) {
        *archiveDataOut = archiveData;
    }
    return 0;
}
