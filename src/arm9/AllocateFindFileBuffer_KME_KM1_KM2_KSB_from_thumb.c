/* Looks up and loads a file in one of the scene archives (probably
 * KME/KM1/KM2/KSB). In menu scenes (id 1, 3 or 12) the main archive
 * (name field +0x28) is tried directly; otherwise three archives
 * (fields +0x18/+0x1c/+0x20, only if loaded at +0x308/+0x378/+0x3e8)
 * are tried in turn until a buffer has been allocated.
 * Path "%s:%s" for absolute paths (starting with '/'), otherwise "%s:/%s". */

extern int GetCurrentSceneId(void);
extern int Util_SNPrintF(char *dst, unsigned int size, const char *fmt, ...);
extern void *AllocateReadFileBuffer_from_thumb(const char *path, int arg);

/* Table of archive/drive names per file type. */
struct SceneArchiveNames {
    char pad_00[0x18];
    char *f18; /* probably "KM1" */
    char *f1c; /* probably "KM2" */
    char *f20; /* probably "KSB" */
    char pad_24[4];
    char *f28; /* probably "KME" */
};
extern struct SceneArchiveNames data_02164e04;

/* Global state with pointers to the loaded archives. */
struct SceneArchiveState {
    char pad_000[0x308];
    void *f308; /* archive 1 loaded? */
    char pad_30c[0x378 - 0x30c];
    void *f378; /* archive 2 loaded? */
    char pad_37c[0x3e8 - 0x37c];
    void *f3e8; /* archive 3 loaded? */
};
extern struct SceneArchiveState *data_021759c8;

extern char data_02165008[]; /* "%s:%s"  */
extern char data_02165010[]; /* "%s:/%s" */
extern char data_02165018[]; /* "%s:%s"  */
extern char data_02165020[]; /* "%s:/%s" */
extern char data_02165028[]; /* "%s:%s"  */
extern char data_02165030[]; /* "%s:/%s" */
extern char data_02165038[]; /* "%s:%s"  */
extern char data_02165040[]; /* "%s:/%s" */

void *AllocateFindFileBuffer_KME_KM1_KM2_KSB_from_thumb(const char *path)
{
    void *result = 0;
    char buf[0x80];
    int scene = GetCurrentSceneId();

    if (scene == 1 || scene == 3 || scene == 0xc) {
        char *name = data_02164e04.f28;
        if (*(const unsigned char *)path == '/') {
            Util_SNPrintF(buf, 0x80, data_02165008, name, path);
        } else {
            Util_SNPrintF(buf, 0x80, data_02165010, name, path);
        }
        result = AllocateReadFileBuffer_from_thumb(buf, 8);
    } else {
        if (data_021759c8->f308 != 0) {
            char *name = data_02164e04.f18;
            if (*(const unsigned char *)path == '/') {
                Util_SNPrintF(buf, 0x80, data_02165018, name, path);
            } else {
                Util_SNPrintF(buf, 0x80, data_02165020, name, path);
            }
            result = AllocateReadFileBuffer_from_thumb(buf, 8);
        }
        if (result == 0 && data_021759c8->f378 != 0) {
            char *name = data_02164e04.f1c;
            if (*(const unsigned char *)path == '/') {
                Util_SNPrintF(buf, 0x80, data_02165028, name, path);
            } else {
                Util_SNPrintF(buf, 0x80, data_02165030, name, path);
            }
            result = AllocateReadFileBuffer_from_thumb(buf, 8);
        }
        if (result == 0 && data_021759c8->f3e8 != 0) {
            char *name = data_02164e04.f20;
            if (*(const unsigned char *)path == '/') {
                Util_SNPrintF(buf, 0x80, data_02165038, name, path);
            } else {
                Util_SNPrintF(buf, 0x80, data_02165040, name, path);
            }
            result = AllocateReadFileBuffer_from_thumb(buf, 8);
        }
    }
    return result;
}
