// PURPOSE: Loads overlay metadata from the ROM.
// The processor and overlay ID select an entry from one of two overlay tables.
// The output receives the table header and the overlay file's ROM position.
// It returns zero when either file cannot be opened or read completely.

typedef unsigned int u32;

typedef struct FSFileId {
    int word0;
    int word1;
} FSFileId;

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
} FSFile;

typedef struct FSOverlayInfoHeader {
    u32 id;
    void *ramAddress;
    u32 ramSize;
    u32 bssSize;
    void *staticInitializersStart;
    void *staticInitializersEnd;
    u32 fileId;
    u32 compressedAndFlags;
} FSOverlayInfoHeader;

typedef struct FSOverlayInfo {
    FSOverlayInfoHeader header;
    int processor;
    u32 fileOffset;
    u32 fileLength;
} FSOverlayInfo;

typedef struct OverlayTableRegion {
    unsigned char *offset;
    u32 length;
} OverlayTableRegion;

extern void Fs_File_Initialize(FSFile *file);
extern int Fs_File_OpenRaw(FSFile *file, void *archive, void *start,
                           void *end, int fileId);
extern int Fs_File_Read(FSFile *file, void *destination, u32 length);
extern void Fs_File_Close(FSFile *file);
extern void Fs_GetOverlayFileId(FSFileId *fileId, FSOverlayInfo *info);
extern int Fs_File_OpenById(FSFile *file, FSFileId fileId);

int Fs_OverlayInfo_DoLoad(FSOverlayInfo *info, int processor, u32 overlayId,
                          void *archive, void *arm9Table, u32 arm9TableLength,
                          void *arm7Table, u32 arm7TableLength)
{
    OverlayTableRegion region;
    u32 position;
    FSFileId fileId;
    FSFile file;

    if (processor == 0) {
        region.offset = arm9Table;
        region.length = arm9TableLength;
    } else {
        region.offset = arm7Table;
        region.length = arm7TableLength;
    }

    position = overlayId * sizeof(FSOverlayInfoHeader);
    if (position >= region.length) {
        return 0;
    }

    Fs_File_Initialize(&file);
    if (Fs_File_OpenRaw(&file, archive, region.offset + position,
                        region.offset + region.length, -1) == 0) {
        return 0;
    }

    if (Fs_File_Read(&file, info, sizeof(FSOverlayInfoHeader)) !=
        sizeof(FSOverlayInfoHeader)) {
        Fs_File_Close(&file);
        return 0;
    }

    Fs_File_Close(&file);
    info->processor = processor;
    Fs_GetOverlayFileId(&fileId, info);
    if (Fs_File_OpenById(&file, fileId) == 0) {
        return 0;
    }

    info->fileOffset = file.field_24;
    info->fileLength = file.field_28 - file.field_24;
    Fs_File_Close(&file);
    return 1;
}
