// PURPOSE: Loads the time trial save section.
// The argument receives the requested save data.
// When save data is available, this starts the corresponding section read.
// The final flag probably selects the normal read path.

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

void ReadSaveDataSection_TimeTrial_from_thumb(void *destination)
{
    if (data_021759d4->saveData != 0) {
        data_021759d4->readDestination = destination;
        ReadSaveChunkImpl_from_thumb(0x800, 0x31700,
                                     data_021759d4->saveStorage, 0x1600,
                                     CopyToSXSomePtr_from_thumb, 0x41544b4e,
                                     0);
    }
}
