// PURPOSE: Finds a file buffer in the current scene archives.
// Tries the main archive in menu scenes, probably KME.
// Otherwise it searches the available KM1, KM2, and KSB archives in order.

typedef struct SceneArchiveNames {
    char pad_00[0x18];
    char *f18;
    char *f1c;
    char *f20;
    char pad_24[4];
    char *f28;
} SceneArchiveNames;

typedef struct ArcRuntimeState {
    char pad_000[0x308];
    void *f308;
    char pad_30c[0x378 - 0x30c];
    void *f378;
    char pad_37c[0x3e8 - 0x37c];
    void *f3e8;
} ArcRuntimeState;

extern int GetCurrentSceneId(void);
extern void *FormatGetPathMountBuffer_from_thumb(char *archiveName, const char *path);
extern SceneArchiveNames data_02164e04;
extern ArcRuntimeState *data_021759c8;

void *FindFileBuffer_KME_KM1_KM2_KSB_from_thumb(const char *path)
{
    void *result = 0;
    int scene = GetCurrentSceneId();

    if (scene == 1 || scene == 3 || scene == 0xc) {
        result = FormatGetPathMountBuffer_from_thumb(data_02164e04.f28, path);
    } else {
        if (data_021759c8->f308 != 0)
            result = FormatGetPathMountBuffer_from_thumb(data_02164e04.f18, path);
        if (result == 0 && data_021759c8->f378 != 0)
            result = FormatGetPathMountBuffer_from_thumb(data_02164e04.f1c, path);
        if (result == 0 && data_021759c8->f3e8 != 0)
            result = FormatGetPathMountBuffer_from_thumb(data_02164e04.f20, path);
    }
    return result;
}
