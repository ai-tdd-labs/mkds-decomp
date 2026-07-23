// PURPOSE: Loads and starts an overlay.
// The arguments probably identify the overlay and its target memory area.
// Temporary overlay information is prepared before loading the image.

typedef unsigned int u32;

typedef struct FSOverlayInfo {
    u32 words[11];
} FSOverlayInfo;

extern int Fs_OverlayInfo_Load(FSOverlayInfo *info, int overlay, int target);
extern int Fs_OverlayInfo_LoadImage(FSOverlayInfo *info);
extern void Fs_OverlayInfo_Start(FSOverlayInfo *info);

int Fs_LoadOverlay(int overlay, int target)
{
    FSOverlayInfo info;

    if (Fs_OverlayInfo_Load(&info, overlay, target) == 0) {
        return 0;
    }
    if (Fs_OverlayInfo_LoadImage(&info) == 0) {
        return 0;
    }
    Fs_OverlayInfo_Start(&info);
    return 1;
}
