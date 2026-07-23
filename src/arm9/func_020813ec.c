/*
 * PURPOSE: Spawns and updates a racer's slipstream/draft trail effect object.
 *
 * Args: idx = racer/driver slot index (r0), v = a VecFx32 direction/position
 * the effect should follow (r1). Looks up the driver entry for the racer.
 * If the driver has a certain flag set (+0x4c bit 0x8000), has no effect
 * object yet (slot +0x28 == 0) and its speed field (+0x2a4) is above 0x1000,
 * it allocates a 0x53-type effect object, remembers the driver entry in it
 * (+0x94) and installs func_02081374 as its handler (+0x90), storing it in
 * the racer's slot. If (still) no object exists it returns.
 * Otherwise it scales the driver velocity (+0x3b0..+0x3b8) by 0.8 and writes
 * it to the object (+0x40), computes an offset position via VecFx32_AddScale1,
 * feeds it to func_0208b5b0, stores v truncated to 16-bit at (+0x50..+0x54)
 * and marks the driver (+0x48 |= 0x400).
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;

typedef struct { int x, y, z; } VecFx32;   /* fx32 3-vector */
typedef struct { s16 x, y, z; } VecFx16;   /* fx16 3-vector */

typedef struct {
    char pad00[0x48];
    int f48;            /* +0x48 flag word, |= 0x400 */
    int f4c;            /* +0x4c flags, tested & 0x8000 */
    char pad50[0x1d0 - 0x50];
    int f1d0;           /* +0x1d0 */
    char pad1d4[0x2a4 - 0x1d4];
    int f2a4;           /* +0x2a4 speed */
    char pad2a8[0x3b0 - 0x2a8];
    VecFx32 f3b0;       /* +0x3b0 velocity */
    char pad3bc[0x508 - 0x3bc];
    int f508;           /* +0x508 heap / scale handle */
} DriverEntry;

struct Effect;

typedef struct {
    char pad00[0x28];
    struct Effect *f28; /* +0x28 effect object pointer */
    char pad2c[0x58 - 0x2c];
} Slot;                 /* stride 0x58 */

typedef struct Effect {
    char pad00[0x40];
    VecFx32 f40;        /* +0x40 scaled velocity */
    char pad4c[0x50 - 0x4c];
    VecFx16 f50;        /* +0x50 direction, 16-bit */
    char pad56[0x90 - 0x56];
    void *f90;          /* +0x90 handler */
    void *f94;          /* +0x94 owning driver entry */
} Effect;

extern void *GetDriverEntry(int idx);
extern Slot *data_0217ae84;
extern void *func_0208b7bc(int type, void *heap);
extern void func_02081374(void);
extern void VecFx32_AddScale1(int a, VecFx32 *v, int s, VecFx32 *out);
extern void func_0208b5b0(void *obj, VecFx32 *v);

void func_020813ec(int idx, VecFx32 *v)
{
    DriverEntry *drv = (DriverEntry *)GetDriverEntry(idx);
    Slot *slot = &data_0217ae84[idx];
    VecFx16 dir;
    VecFx32 vel;
    VecFx32 pos;

    if ((drv->f4c & 0x8000) && slot->f28 == 0 && drv->f2a4 > 0x1000) {
        Effect *e = (Effect *)func_0208b7bc(0x53, (void *)drv->f508);
        e->f94 = drv;
        e->f90 = (void *)func_02081374;
        slot->f28 = e;
    }

    if (slot->f28 == 0)
        return;

    vel.x = (int)(((long long)drv->f3b0.x * 0xCCD) >> 12);
    vel.y = (int)(((long long)drv->f3b0.y * 0xCCD) >> 12);
    vel.z = (int)(((long long)drv->f3b0.z * 0xCCD) >> 12);
    slot->f28->f40 = vel;

    VecFx32_AddScale1(-drv->f1d0, v, drv->f508, &pos);
    func_0208b5b0(slot->f28, &pos);

    dir.x = (s16)v->x;
    dir.y = (s16)v->y;
    dir.z = (s16)v->z;
    slot->f28->f50 = dir;

    drv->f48 |= 0x400;
}
