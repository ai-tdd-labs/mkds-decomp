// PURPOSE: Loads every sound asset in a sound group.
// The group ID selects a list of sequences, banks, wave archives, and archives.
// The heap is used while each listed asset is prepared.
// Returns the first load error, or zero after the whole group is loaded.

typedef unsigned int u32;
typedef unsigned char u8;

typedef struct SoundGroupItem {
    u8 type;
    u8 loadFlags;
    u8 padding[2];
    u32 id;
} SoundGroupItem;

typedef struct SoundGroupInfo {
    u32 itemCount;
    SoundGroupItem items[1];
} SoundGroupInfo;

extern SoundGroupInfo *Sound_GetGroupInfoEntry(u32 groupId);
extern int NNSi_SndArcLoadSeq(u32 sequenceId, u8 flags, void *heap,
                              int preparationOption, void **sequenceDataOut);
extern int Sound_GetSbnkPointer(u32 bankId, u8 flags, void *heap,
                                int preparationOption, void **bankDataOut);
extern int Sound_GetSwarPointer(int waveArchiveId, u32 flags, void *heap,
                                int preparationOption, void **waveDataOut);
extern int Sound_GetSarcPointer(int archiveId, u32 flags, void *heap,
                                int preparationOption, void **archiveDataOut);

int Sound_LoadGroupImpl(u32 groupId, void *heap)
{
    SoundGroupInfo *groupInfo;
    u32 i;

    groupInfo = Sound_GetGroupInfoEntry(groupId);
    if (groupInfo == 0) {
        return 1;
    }

    for (i = 0; i < groupInfo->itemCount; i++) {
        SoundGroupItem *item = &groupInfo->items[i];
        int result;

        switch (item->type) {
        case 0:
            result = NNSi_SndArcLoadSeq(item->id, item->loadFlags,
                                        heap, 1, 0);
            if (result != 0) {
                return result;
            }
            break;

        case 3:
            result = Sound_GetSarcPointer(item->id, item->loadFlags,
                                          heap, 1, 0);
            if (result != 0) {
                return result;
            }
            break;

        case 1:
            result = Sound_GetSbnkPointer(item->id, item->loadFlags,
                                          heap, 1, 0);
            if (result != 0) {
                return result;
            }
            break;

        case 2:
            result = Sound_GetSwarPointer(item->id, item->loadFlags,
                                          heap, 1, 0);
            if (result != 0) {
                return result;
            }
            break;
        }
    }

    return 0;
}
