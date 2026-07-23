// PURPOSE: Loads the emblem section of the save file.
// The argument is retained as the destination while the save operation is active.
// It probably requests the 0x300-byte emblem chunk from the current save storage.

typedef unsigned int u32;

typedef struct SaveDataHolder {
    unsigned char pad_00[0x0c];
    void *saveData;
    unsigned char pad_10[0x50];
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

void ReadSaveDataSection_Emblem_from_thumb(void *destination)
{
    if (data_021759d4->saveData != 0) {
        data_021759d4->readDestination = destination;
        ReadSaveChunkImpl_from_thumb(0x100, 0x31000,
                                     data_021759d4->saveStorage, 0x300,
                                     CopyToSXSomePtr_from_thumb, 0x4d454b4e,
                                     0);
    }
}
