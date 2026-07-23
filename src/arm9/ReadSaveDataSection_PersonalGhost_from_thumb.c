// PURPOSE: Loads a personal ghost record from the save file.
// The first argument selects the ghost slot and the second is saved as request context.
// If a save source is available, it starts an asynchronous 0xe00-byte read.
// The validation value probably identifies the personal-ghost section.

typedef unsigned int u32;
typedef void (*SaveCopyCallback)(void *destination, const void *source,
                                 u32 size);

struct SaveDataState {
    unsigned char unused_00[0x0c];
    void *saveSource;
    unsigned char unused_10[0x50];
    void *personalGhostBuffer;
    unsigned char unused_64[4];
    u32 requestContext;
};

extern struct SaveDataState *data_021759d4;
extern void CopyToSXSomePtr_from_thumb(void *destination, const void *source,
                                       u32 size);
extern void ReadSaveChunkImpl2_from_thumb(u32 saveOffset, void *destination,
                                          u32 size,
                                          SaveCopyCallback copyCallback,
                                          u32 validationCode);

void ReadSaveDataSection_PersonalGhost_from_thumb(u32 ghostSlot,
                                                   u32 requestContext)
{
    u32 saveOffset = ghostSlot * 0xe00;
    struct SaveDataState *saveData = data_021759d4;
    void *destination = saveData->personalGhostBuffer;

    if (saveData->saveSource != 0) {
        saveData->requestContext = requestContext;
        ReadSaveChunkImpl2_from_thumb(saveOffset + 0xaf00, destination,
                                      0xe00, CopyToSXSomePtr_from_thumb,
                                      0x47504b4e);
    }
}
