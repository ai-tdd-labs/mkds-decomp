// PURPOSE: Loads an overlay's metadata and file location.
// The processor and overlay ID select the matching overlay-table entry.
// It uses the cached table when available and otherwise reads the ROM header.
// It returns zero when the entry or its backing file cannot be found.

typedef unsigned char u8;
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
    u8 *offset;
    u32 length;
} OverlayTableRegion;

extern OverlayTableRegion data_0216f35c;
extern OverlayTableRegion data_0216f364;
extern u8 data_0216f36c[];

extern void Mem_CpuCopy8(const void *source, void *destination, u32 length);
extern void Fs_File_Initialize(FSFile *file);
extern void Fs_GetOverlayFileId(FSFileId *fileId, FSOverlayInfo *info);
extern int Fs_File_OpenById(FSFile *file, FSFileId fileId);
extern void Fs_File_Close(FSFile *file);
extern int Fs_OverlayInfo_DoLoad(FSOverlayInfo *info, int processor,
                                 u32 overlayId, void *archive,
                                 void *arm9Table, u32 arm9TableLength,
                                 void *arm7Table, u32 arm7TableLength);

int Fs_OverlayInfo_Load(FSOverlayInfo *info, int processor, u32 overlayId)
{
    OverlayTableRegion *region =
        (processor == 0) ? &data_0216f35c : &data_0216f364;

    if (region->offset != 0) {
        FSFileId fileId;
        FSFile file;
        u32 position = overlayId * sizeof(FSOverlayInfoHeader);

        if (position >= region->length) {
            return 0;
        }

        Mem_CpuCopy8(region->offset + position, info,
                     sizeof(FSOverlayInfoHeader));
        info->processor = processor;
        Fs_File_Initialize(&file);
        Fs_GetOverlayFileId(&fileId, info);
        if (Fs_File_OpenById(&file, fileId) == 0) {
            return 0;
        }

        info->fileOffset = file.field_24;
        info->fileLength = file.field_28 - file.field_24;
        Fs_File_Close(&file);
        return 1;
    } else {
        volatile OverlayTableRegion *arm9Table =
            (volatile OverlayTableRegion *)0x027ffe50;
        volatile OverlayTableRegion *arm7Table =
            (volatile OverlayTableRegion *)0x027ffe58;

        return Fs_OverlayInfo_DoLoad(info, processor, overlayId,
                                     data_0216f36c,
                                     arm9Table->offset, arm9Table->length,
                                     arm7Table->offset, arm7Table->length);
    }
}
