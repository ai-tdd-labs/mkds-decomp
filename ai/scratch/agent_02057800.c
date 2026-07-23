// PURPOSE: Loads a selected ghost record from the save file.
/* The first argument selects the ghost format, the second selects its slot,
 * and the third is retained as request context while loading. */

typedef unsigned int u32;

typedef void (*SaveCopyCallback)(void *destination, const void *source,
                                 u32 size);

struct SaveDataState {
    unsigned char pad_00[0x0c];
    void *saveSource;
    unsigned char pad_10[0x50];
    void *ghostBuffer;
    unsigned char pad_64[4];
    u32 requestContext;
};

extern struct SaveDataState *data_021759d4;
extern void ReadSaveChunkImpl2_from_thumb(u32 saveOffset, void *destination,
                                          u32 size, u32 validationCode,
                                          SaveCopyCallback copyCallback);
extern void CopyToSXSomePtr0x30_from_thumb(void *destination,
                                           const void *source, u32 size);
extern void CopyToSXSomePtr0x230_from_thumb(void *destination,
                                            const void *source, u32 size);

void func_02057800(int ghostType, u32 ghostSlot, u32 requestContext)
{
    u32 baseOffset;
    u32 chunkSize;
    void *destination;
    u32 validationCode;
    SaveCopyCallback copyCallback;
    struct SaveDataState *saveData = data_021759d4;

    if (saveData->saveSource != 0) {
        if (ghostType != 0) {
            baseOffset = 0;
            chunkSize = 0xe00;
            ghostSlot *= chunkSize;
            destination = saveData->ghostBuffer;
            validationCode = 0x47504b4e;
            copyCallback = CopyToSXSomePtr0x30_from_thumb;
        } else {
            baseOffset = 0x1c000;
            chunkSize = 0x1000;
            ghostSlot <<= 12;
            destination = saveData->ghostBuffer;
            validationCode = 0x47444b4e;
            copyCallback = CopyToSXSomePtr0x230_from_thumb;
        }

        saveData->requestContext = requestContext;
        ReadSaveChunkImpl2_from_thumb(ghostSlot + (baseOffset + 0xaf00),
                                      destination, chunkSize, validationCode,
                                      copyCallback);
    }
}
