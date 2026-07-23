/* PURPOSE: Loads the header section of the save file.
 * The argument is saved as callback context while a save operation is active.
 * It reads 0x100 bytes from the header area into the current save buffer and
 * probably validates the section with its NKSY identifier. */

typedef unsigned int u32;

struct SaveDataHolder {
    unsigned char unk_00[0x0c];
    int operationActive;
    unsigned char unk_10[0x50];
    void *saveBuffer;
    unsigned char unk_64[4];
    void *callbackContext;
};

extern struct SaveDataHolder *data_021759d4;
extern void CopyToSXSomePtr_from_thumb(void);
extern void ReadSaveChunkImpl_from_thumb(
    int sectionOffset,
    u32 saveOffset,
    void *destination,
    u32 size,
    void (*copyCallback)(void),
    u32 sectionId,
    int option);

void ReadSaveDataSection_Header_from_thumb(void *callbackContext)
{
    if (data_021759d4->operationActive != 0) {
        data_021759d4->callbackContext = callbackContext;
        ReadSaveChunkImpl_from_thumb(
            0,
            0x30f00,
            data_021759d4->saveBuffer,
            0x100,
            CopyToSXSomePtr_from_thumb,
            0x59534b4e,
            1);
    }
}
