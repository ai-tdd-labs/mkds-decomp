/*
 * PURPOSE: Aims a kart's item (e.g. a shell) at a target vector, or at the
 * current driver's aim point if no target vector is given.
 *
 * arg0 (r0): kart/actor object, forwarded as the first arg to func_0209b388.
 * arg1 (r1): optional pointer to a struct holding a VecFx32-like direction
 *            at offset 0x5c/0x60/0x64 and an item-slot struct at +0x50.
 *            May be NULL.
 * arg2 (r2): pointer to a mode byte; only mode==1 does real work.
 * arg3 (r3): pointer to a return-status byte, returned as the result.
 *
 * When mode==1 and arg1 is non-NULL: if the direction vector at
 * arg1->0x5c/0x60/0x64 is (almost) zero-length (squared length < 0x10),
 * pass a zero direction; otherwise normalize it first. Either way, feed the
 * (possibly normalized) direction into func_0209b388, then call
 * func_020f8ddc(arg1).
 *
 * When mode==1 and arg1 is NULL: look up the current driver (via
 * gRaceConfig's signed byte field at offset 0x62) and aim using fields from
 * that driver's entry instead.
 */
extern void Vector3_MaybeNormalize(void *in, void *out);
extern void func_0209b388(void *a0, void *a1, void *a2, void *a3);
extern void func_020f8ddc(void *a0);
extern void *GetDriverEntry(int driverIndex);

typedef struct {
    signed char pad[0x62];
    signed char driverIndexByte; /* offset 0x62 */
} RaceConfigExt;

extern RaceConfigExt *gRaceConfig;

typedef struct {
    char pad[0x5c];
    int x; /* 0x5c */
    int y; /* 0x60 */
    int z; /* 0x64 */
} DirHolder;

int func_0209b270(void *arg0, void *arg1, unsigned char *modePtr, unsigned char *statusPtr)
{
    unsigned char mode = *modePtr;
    unsigned char status = *statusPtr;

    if (mode == 1) {
        if (arg1 != 0) {
            DirHolder *dir = (DirHolder *)arg1;
            long long lenSq = (long long)dir->x * dir->x + (long long)dir->y * dir->y + (long long)dir->z * dir->z;
            if (lenSq >= 0x10) {
                int normalized[3];
                Vector3_MaybeNormalize(&dir->x, normalized);
                func_0209b388(arg0, (char *)arg1 + 0x50, normalized, 0);
            } else {
                func_0209b388(arg0, (char *)arg1 + 0x50, 0, 0);
            }
            func_020f8ddc(arg1);
        } else {
            void *driver = GetDriverEntry((unsigned short)gRaceConfig->driverIndexByte);
            func_0209b388(arg0, (char *)driver + 0x80, (char *)driver + 0x68, (char *)driver + 0xa4);
        }
    }

    return status & 0xff;
}
