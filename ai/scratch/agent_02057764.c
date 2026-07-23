// PURPOSE: Loads the Friend List save section.
// The argument receives the loaded Friend List data.
// When a save operation is active, this records the destination and starts
// the matching save-chunk read.

typedef unsigned int u32;

typedef struct SaveDataHolder {
    unsigned char pad_00[0x0c];
    void *saveData;
    unsigned char pad_10[0x4c];
    int readStatus;
    void *saveStorage;
    unsigned char pad_64[4];
    void *readDestination;
} SaveDataHolder;

typedef void (*SaveChunkCopyCallback)(void *source, u32 size);

extern SaveDataHolder *data_021759d4;
extern void CopyToSXSomePtr_from_thumb(void *source, u32 size);
extern void ReadSaveChunkImpl_from_thumb(u32 size, u32 offset,
                                         void *saveStorage, u32 copySize,
                                         SaveChunkCopyCallback copyCallback,
                                         u32 sectionTag, int flag);

void ReadSaveDataSection_FriendList_from_thumb(void *destination)
{
    if (data_021759d4->saveData != 0) {
        data_021759d4->readDestination = destination;
        data_021759d4->readStatus = -1;
        ReadSaveChunkImpl_from_thumb(0x1f00, 0x32e00,
                                     data_021759d4->saveStorage, 0xc00,
                                     CopyToSXSomePtr_from_thumb, 0x4c464b4e,
                                     0);
    }
}
