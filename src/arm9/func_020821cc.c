// PURPOSE: Aims an object ahead of the player and adjusts its steering value.
// The second argument skips the update when it is nonzero.
// A driver state flag probably changes how far ahead the target is placed.
// The target follows the driver's path height and a shared reference position.

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct {
    char pad9c[0x9c];
    VecFx32 f9c;
    char padA8[0x15c - 0xa8];
    VecFx32 f15c;
} HD;

typedef struct {
    char pad0[0x44];
    int f44;
    char pad48[0x2a4 - 0x48];
    int f2a4;
    char pad2a8[0x508 - 0x2a8];
    int *f508;
} DriverEntry;

typedef struct {
    int f0;
    int f4;
    int f8;
    int fc;
} Ref;

typedef struct {
    char pad0[0x20];
    Ref **f20;
    char pad24[0x28 - 0x24];
    int f28;
    int f2c;
    int f30;
    char pad34[0x58 - 0x34];
    int f58;
} Obj;

typedef struct {
    char pad62[0x62];
    signed char f62;
} RaceConfig;

extern HD *GetGlobalHD5(void);
extern DriverEntry *GetDriverEntry(int id);
extern void Vector3_MaybeNormalize(VecFx32 *dst, VecFx32 *src);
extern void VecFx32_AddScale1(int scale, VecFx32 *dir, VecFx32 *base,
                              VecFx32 *out);
extern RaceConfig *gRaceConfig;
extern int data_0217ae9c;

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_020821cc(Obj *obj, int skip)
{
    HD *hd;
    DriverEntry *de1;
    DriverEntry *de2;
    VecFx32 v;
    VecFx32 out;
    int distanceAdjust;
    int speed;

    if (skip)
        return;

    hd = GetGlobalHD5();
    de1 = GetDriverEntry(gRaceConfig->f62);

    v = hd->f15c;
    speed = FX_Mul(de1->f2a4, data_0217ae9c);
    distanceAdjust = 0;
    v.y = 0;

    if (speed > 0x1000)
        speed = 0x1000;
    if (de1->f44 & 0x100)
        distanceAdjust = -0x5800;

    /* Include the zero Y term to preserve the three-term fx64 sum. */
    if ((long long)v.x * v.x + (long long)v.y * v.y +
        (long long)v.z * v.z >= 0x10)
        Vector3_MaybeNormalize(&v, &v);

    VecFx32_AddScale1(0x5800 + FX_Mul(distanceAdjust * 3, speed),
                      &v, &hd->f9c, &out);

    de2 = GetDriverEntry(gRaceConfig->f62);
    out.y = de2->f508[1] >> 4;

    obj->f28 = out.x + (*obj->f20)->f4;
    obj->f2c = out.y + (*obj->f20)->f8;
    obj->f30 = out.z + (*obj->f20)->fc;
    obj->f58 = FX_Mul(speed, 0x800);
}
