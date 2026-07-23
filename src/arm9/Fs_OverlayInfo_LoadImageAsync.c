// PURPOSE: Loads an overlay image into its assigned memory asynchronously.
/*
 * The overlay information supplies the image buffer and file identifier.
 * The file is closed when starting the read fails.
 */

typedef unsigned int u32;

typedef struct FSFile FSFile;

typedef struct FSFileId {
    u32 word0;
    u32 word1;
} FSFileId;

typedef struct FSOverlayInfo {
    u32 unknown_00;
    void *image;
} FSOverlayInfo;

extern void Fs_File_Initialize(FSFile *f);
extern int Fs_File_OpenById(FSFile *f, FSFileId fileId);
extern u32 Fs_File_ReadAsync(FSFile *f, void *buffer, u32 size);
extern void Fs_File_Close(FSFile *f);
extern void Fs_GetOverlayFileId(FSFileId *fileId, FSOverlayInfo *info);
extern void Fs_OverlayInfo_ClearImage(FSOverlayInfo *info);
extern u32 Fs_OverlayInfo_GetBinarySize(FSOverlayInfo *info);

int Fs_OverlayInfo_LoadImageAsync(FSOverlayInfo *info, FSFile *file)
{
    FSFileId fileId;
    u32 size;

    Fs_File_Initialize(file);
    Fs_GetOverlayFileId(&fileId, info);
    if (Fs_File_OpenById(file, fileId) == 0) {
        return 0;
    }

    size = Fs_OverlayInfo_GetBinarySize(info);
    Fs_OverlayInfo_ClearImage(info);
    if (Fs_File_ReadAsync(file, info->image, size) == size) {
        return 1;
    }

    Fs_File_Close(file);
    return 0;
}
