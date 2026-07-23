typedef unsigned char u8;
typedef unsigned int u32;

typedef struct SaveDataHolder {
    u8 unknown_00[0x40];
    u8 *ghostData;
} SaveDataHolder;

extern SaveDataHolder *data_0217aa08;

extern void FormatGhostBinPath(u8 ghostId, char *path, u32 pathSize);
extern void OpenReadFileBufferSize_from_thumb(const char *path, void *destination,
                                              u32 size);
extern void ResetSaveDataHolderTaskPendingFlag_from_thumb(void);

// PURPOSE: Loads every saved ghost replay into the supplied ghost-data buffer.
void Task_ReadGhostBins(void)
{
    char path[0x80];
    u8 ghostId;

    for (ghostId = 0; ghostId < 0x20; ghostId++) {
        FormatGhostBinPath(ghostId, path, 0x80);
        OpenReadFileBufferSize_from_thumb(
            path, data_0217aa08->ghostData + ghostId * 0x230, 0x230);
    }

    ResetSaveDataHolderTaskPendingFlag_from_thumb();
    data_0217aa08->ghostData = 0;
}
