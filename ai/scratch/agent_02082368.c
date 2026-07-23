/* PURPOSE: Steers a kart/camera toward a spot ahead on the track and also
   sets its turn/lean amount from the current player's speed.
   obj  = the kart/aim object (r0).
   skip = if nonzero, do nothing this frame (r1).
   Grabs the current player's horizontal heading vector (HD5 +0x15c),
   flattens it to the X/Z plane (Y=0), normalises it if long enough
   (squared length >= 0x10), scales it by 0x5800 and adds the base
   position (HD5 +0x9c) to get a target point. The target's Y is taken
   from the current driver's path node (>>4). The point is then added to
   a shared reference position (**obj->0x20 fields +4/+8/+c) and stored at
   obj 0x28/0x2c/0x30. Finally obj+0x58 gets a lean/turn value derived
   from the driver's speed (0x2a4) times a global factor, clamped and
   scaled by 0.25. */

typedef struct { int x, y, z; } VecFx32;

typedef struct {
    char pad9c[0x9c];
    VecFx32 f9c;                    /* base position vector */
    char pad2[0x15c - 0x9c - 12];
    VecFx32 f15c;                   /* heading vector (flattened, normalised) */
} HD;

typedef struct {
    char pad0[0x2a4];
    int f2a4;                       /* +0x2a4: speed */
    char pad2a8[0x508 - 0x2a8];
    int *f508;                      /* +0x508: path node {f0,f4,f8} */
} DriverEntry;

typedef struct { int f0, f4, f8, fc; } Ref;

typedef struct {
    char pad0[0x20];
    Ref **f20;                      /* +0x20: ptr to ptr to reference position */
    char pad24[0x28 - 0x24];
    int f28, f2c, f30;              /* +0x28/2c/30: scrolled coords */
    char pad34[0x58 - 0x34];
    int f58;                        /* +0x58: lean/turn amount */
} Obj;

typedef struct { char pad62[0x62]; signed char f62; } RaceConfig;

extern HD *GetGlobalHD5(void);
extern DriverEntry *GetDriverEntry(int id);
extern void Vector3_MaybeNormalize(VecFx32 *dst, VecFx32 *src);
extern void VecFx32_AddScale1(int scale, VecFx32 *dir, VecFx32 *base, VecFx32 *out);
extern RaceConfig *gRaceConfig;
extern int data_0217ae9c;

static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_02082368(Obj *obj, int skip)
{
    HD *hd;
    DriverEntry *de1, *de2;
    VecFx32 v;
    VecFx32 out;
    int m;

    if (skip)
        return;

    hd = GetGlobalHD5();
    de1 = GetDriverEntry(gRaceConfig->f62);

    v = hd->f15c;                   /* ldm/stm 3-word copy */
    v.y = 0;
    /* squared horizontal length as fx64; reassoc swaps first two terms */
    if ((long long)v.x * v.x + (long long)v.y * v.y + (long long)v.z * v.z >= 0x10)
        Vector3_MaybeNormalize(&v, &v);

    VecFx32_AddScale1(0x5800, &v, &hd->f9c, &out);

    de2 = GetDriverEntry(gRaceConfig->f62);
    out.y = de2->f508[1] >> 4;

    obj->f28 = out.x + (*obj->f20)->f4;   /* base pointer reloaded per coord */
    obj->f2c = out.y + (*obj->f20)->f8;
    obj->f30 = out.z + (*obj->f20)->fc;

    m = FX_Mul(de1->f2a4, data_0217ae9c);
    if (m > 0x1000)
        m = 0x1000;
    obj->f58 = FX_Mul(0x1000 - m, 0x400);
}
