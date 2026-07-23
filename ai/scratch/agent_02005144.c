// PURPOSE: Unloads a loaded overlay from memory.
// The two arguments probably identify the overlay and its load target.
// It builds temporary overlay information, then releases the overlay image.
// Returns one only when both operations succeed.

typedef unsigned int u32;

typedef struct FSOverlayInfo {
    u32 words[11];
} FSOverlayInfo;

extern int Fs_OverlayInfo_Load(FSOverlayInfo *info, int overlay, int target);
extern int Fs_OverlayInfo_UnloadImage(FSOverlayInfo *info);

int Fs_UnloadOverlay(int overlay, int target)
{
    FSOverlayInfo info;

    if (Fs_OverlayInfo_Load(&info, overlay, target) != 0) {
        if (Fs_OverlayInfo_UnloadImage(&info) != 0) {
            goto success;
        }
    }
    return 0;

success:
    return 1;
}
