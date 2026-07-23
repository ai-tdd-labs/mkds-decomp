// PURPOSE: Loads a selected ghost record from the save file.
/* The first argument probably selects the ghost format, and the second selects
 * its slot. The third argument is stored as context for the asynchronous read.
 * If no save source is available, the function does nothing. */

typedef unsigned int u32;

typedef void (*SaveCopyCallback)(void *destination, const void *source,
                                 u32 size);

struct SaveDataState {
    unsigned char unused_00[0x0c];
    void *saveSource;
    unsigned char unused_10[0x50];
    void *ghostBuffer;
    unsigned char unused_64[4];
    u32 requestContext;
};

extern struct SaveDataState *data_021759d4;
extern void ReadSaveChunkImpl2_from_thumb(u32 saveOffset, void *destination,
                                          u32 size,
                                          SaveCopyCallback copyCallback,
                                          u32 validationCode);
extern void CopyToSXSomePtr0x30_from_thumb(void *destination,
                                           const void *source, u32 size);

void func_0205786c(int ghostType, u32 ghostSlot, u32 requestContext)
{
    u32 validationCode;
    u32 chunkSize;
    void *destination;
    u32 baseOffset;
    struct SaveDataState *saveData = data_021759d4;

    if (saveData->saveSource != 0) {
        if (ghostType != 0) {
            baseOffset = 0;
            chunkSize = 0xe00;
            ghostSlot *= chunkSize;
            destination = saveData->ghostBuffer;
            validationCode = 0x47504b4e;
        } else {
            baseOffset = 0x1c000;
            chunkSize = 0x1000;
            ghostSlot <<= 12;
            destination = saveData->ghostBuffer;
            validationCode = 0x47444b4e;
        }

        saveData->requestContext = requestContext;
        ReadSaveChunkImpl2_from_thumb(
            ghostSlot + (baseOffset + 0xaf00), destination, chunkSize,
            CopyToSXSomePtr0x30_from_thumb, validationCode);
    }
}
