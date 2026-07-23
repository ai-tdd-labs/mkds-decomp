/* PURPOSE: Loads the saved Grand Prix records into a destination buffer.
 * The argument is the destination for the loaded records. If save data is
 * available, this stores that destination and requests the Grand Prix chunk.
 * The exact meaning of the final zero flag is uncertain. */

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

void ReadSaveDataSection_GrandPrix_from_thumb(void *destination)
{
    if (data_021759d4->saveData != 0) {
        data_021759d4->readDestination = destination;
        ReadSaveChunkImpl_from_thumb(0x400, 0x31300,
                                    data_021759d4->saveStorage, 0x400,
                                    CopyToSXSomePtr_from_thumb, 0x50474b4e,
                                    0);
    }
}
