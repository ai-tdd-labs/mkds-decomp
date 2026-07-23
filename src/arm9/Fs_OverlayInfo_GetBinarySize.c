typedef unsigned int u32;
typedef struct FSOverlayInfo {
    u32 pad_00[2];
    u32 compressedSize;   /* 0x08 */
    u32 pad_0C[4];        /* 0x0c..0x1b */
    u32 ramSize : 24;     /* 0x1c bits 0-23 */
    u32 flags   : 8;      /* 0x1f */
} FSOverlayInfo;
u32 Fs_OverlayInfo_GetBinarySize(FSOverlayInfo *info) {
    if (info->flags & 1) {
        return info->ramSize;
    }
    return info->compressedSize;
}
