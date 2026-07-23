// PURPOSE: Finds a mounted archive buffer for a file path.

typedef struct SceneArchiveNames {
    char pad_00[0x14];
    char *f14;
    char pad_18[0xc];
    char *f24;
    char pad_28[4];
    char *f2c;
    char *f30;
} SceneArchiveNames;

typedef struct ArcRuntimeState {
    char pad_000[0x458];
    void *f458;
    char pad_45c[0x538 - 0x45c];
    void *f538;
    char pad_53c[0x5a8 - 0x53c];
    void *f5a8;
} ArcRuntimeState;

extern SceneArchiveNames data_02164e04;
extern ArcRuntimeState *data_021759c8;
extern void *FormatGetPathMountBuffer_from_thumb(char *name, char *path);
extern int GetCurrentSceneId(void);

void *find_buf_fn_from_thumb(char *path)
{
    void *buf;

    buf = FormatGetPathMountBuffer_from_thumb(data_02164e04.f14, path);
    if (buf == 0 && data_021759c8->f458 != 0) {
        buf = FormatGetPathMountBuffer_from_thumb(data_02164e04.f24, path);
    }
    if (GetCurrentSceneId() == 2) {
        if (buf == 0 && data_021759c8->f538 != 0) {
            buf = FormatGetPathMountBuffer_from_thumb(data_02164e04.f2c, path);
        }
        if (buf == 0 && data_021759c8->f5a8 != 0) {
            buf = FormatGetPathMountBuffer_from_thumb(data_02164e04.f30, path);
        }
    }
    return buf;
}
