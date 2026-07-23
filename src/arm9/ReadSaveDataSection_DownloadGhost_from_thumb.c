// PURPOSE: Loads a downloaded ghost record from the save file.
// The first argument selects the downloaded ghost slot and the second is saved as request context.
// If save data is available, it starts a 0x1000-byte read for that ghost.
// The section identifier probably validates the downloaded-ghost data.

typedef unsigned char u8;
typedef unsigned int u32;

typedef void (*SaveCopyCallback)(void *destination, const void *source,
                                 u32 size);

struct SaveDataState {
    u8 unused_00[0x0c];
    void *saveSource;
    u8 unused_10[0x50];
    void *downloadGhostBuffer;
    u8 unused_64[4];
    void *requestContext;
    u8 ghostSlot;
};

extern struct SaveDataState *data_021759d4;
extern void CopyToSXSomePtr_from_thumb(void *destination, const void *source,
                                       u32 size);
extern void ReadSaveChunkImpl2_from_thumb(u32 saveOffset, void *destination,
                                          u32 size,
                                          SaveCopyCallback copyCallback,
                                          u32 validationCode);

void ReadSaveDataSection_DownloadGhost_from_thumb(u8 ghostSlot,
                                                   void *requestContext)
{
    u32 saveOffset = ghostSlot << 12;
    struct SaveDataState *saveData = data_021759d4;

    if (saveData->saveSource != 0) {
        saveData->requestContext = requestContext;
        data_021759d4->ghostSlot = ghostSlot;
        ReadSaveChunkImpl2_from_thumb(saveOffset + 0x26f00,
                                      ((struct SaveDataState *)data_021759d4)->downloadGhostBuffer,
                                      0x1000, CopyToSXSomePtr_from_thumb,
                                      0x47444b4e);
    }
}
