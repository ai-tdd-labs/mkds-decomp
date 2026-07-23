// PURPOSE: Loads the Mission Run save section.
// The argument receives the loaded Mission Run data.
// When a save operation is active, this records the destination and starts
// the matching save-chunk read. The final flag probably selects normal reading.

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

void ReadSaveDataSection_MissionRun_from_thumb(void *destination)
{
    if (data_021759d4->saveData != 0) {
        data_021759d4->readDestination = destination;
        ReadSaveChunkImpl_from_thumb(0x1e00, 0x32d00,
                                     data_021759d4->saveStorage, 0x100,
                                     CopyToSXSomePtr_from_thumb, 0x524d4b4e,
                                     0);
    }
}
