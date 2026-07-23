// PURPOSE: Loads an overlay's image data into its memory buffer.
// The argument describes the overlay and its destination memory.
// It opens the overlay file, clears the old image, and reads the expected size.
// It returns whether the complete image was loaded successfully.

typedef unsigned int u32;

typedef struct FSFile {
    int field_00;
    int field_04;
    int field_08;
    int field_0c;
    int field_10;
    int field_14;
    int field_18;
    int field_1c;
    int field_20;
    int field_24;
    int field_28;
    int field_2c;
    int field_30;
    int field_34;
    int field_38;
    int field_3c;
    int field_40;
    int field_44;
    int field_48;
} FSFile;

typedef struct FsFileId {
    int word0;
    int word1;
} FsFileId;

typedef struct FSOverlayInfo {
    int field_00;
    void *image;
} FSOverlayInfo;

extern void Fs_File_Initialize(FSFile *f);
extern int Fs_File_OpenById(FSFile *f, FsFileId id);
extern int Fs_File_Read(FSFile *f, void *buffer, u32 size);
extern void Fs_File_Close(FSFile *f);
extern void Fs_GetOverlayFileId(FsFileId *id, FSOverlayInfo *info);
extern void Fs_OverlayInfo_ClearImage(FSOverlayInfo *info);
extern u32 Fs_OverlayInfo_GetBinarySize(FSOverlayInfo *info);

int Fs_OverlayInfo_LoadImage(FSOverlayInfo *info)
{
    FsFileId id;
    FSFile file;
    u32 size;

    Fs_File_Initialize(&file);
    Fs_GetOverlayFileId(&id, info);
    if (Fs_File_OpenById(&file, id) == 0) {
        return 0;
    }

    size = Fs_OverlayInfo_GetBinarySize(info);
    Fs_OverlayInfo_ClearImage(info);
    if (Fs_File_Read(&file, info->image, size) != size) {
        Fs_File_Close(&file);
        return 0;
    }

    Fs_File_Close(&file);
    return 1;
}
