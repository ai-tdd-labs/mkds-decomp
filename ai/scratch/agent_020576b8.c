// PURPOSE: Loads the NKFE save section.
/* The first argument receives the loaded data and the second selects its slot.
 * When a save operation is active, this records the destination and starts
 * the matching section read.
 */

typedef unsigned int u32;

typedef struct SaveDataHolder {
    unsigned char pad_00[0x0c];
    void *operationActive;
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

void ReadSaveDataSection_NKFE_from_thumb(void *destination, int slot)
{
    u32 offset = slot * 0xb00;

    if (data_021759d4->operationActive != 0) {
        data_021759d4->readDestination = destination;
        data_021759d4->readStatus = -1;
        ReadSaveChunkImpl_from_thumb(offset + 0x2b00, offset + 0x33a00,
                                     data_021759d4->saveStorage, 0xb00,
                                     CopyToSXSomePtr_from_thumb, 0x45464b4e,
                                     0);
    }
}
