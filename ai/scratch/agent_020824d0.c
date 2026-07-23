// PURPOSE: Aims an object along the current kart direction and updates its orientation.
// The second argument skips the update when it is nonzero.
// The routine builds a target point from the current heading and a shared base position.
// It probably also copies an orientation vector into the object's rotation fields.

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct {
    short x;
    short y;
    short z;
} VecFx16;

typedef struct {
    char pad9c[0x9c];
    VecFx32 f9c;
    char pad_a8[0x15c - 0x9c - 12];
    VecFx32 f15c;
} HD;

typedef struct {
    int f0;
    int f4;
    int f8;
    int fc;
} Ref;

typedef struct {
    char pad0[0x20];
    Ref **f20;
    int f24;
    int f28;
    int f2c;
    int f30;
    char pad34[0x50 - 0x34];
    short f50;
    short f52;
    short f54;
    char pad56[0x68 - 0x56];
    int f68;
} Obj;

typedef struct {
    char pad62[0x62];
    signed char f62;
} RaceConfig;

extern HD *GetGlobalHD4(void);
extern void *GetDriverEntry(int id);
extern void Vector3_MaybeNormalize(VecFx32 *dst, VecFx32 *src);
extern void VecFx32_CrossProduct(const VecFx32 *a, const VecFx32 *b,
                                 VecFx32 *out);
extern void VecFx32_AddScale1(int scale, VecFx32 *dir, VecFx32 *base,
                              VecFx32 *out);
extern RaceConfig *gRaceConfig;
extern VecFx32 data_02155a08;
extern int data_02165960;
extern int data_02165964;
extern int data_02165968;

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_020824d0(Obj *obj, int skip)
{
    VecFx16 rotation;
    VecFx32 direction;
    VecFx32 cross;
    VecFx32 target;
    VecFx32 axis;
    HD *hd;

    if (skip)
        return;

    hd = GetGlobalHD4();
    GetDriverEntry(gRaceConfig->f62);

    direction = hd->f15c;
    direction.y = 0;
    axis = data_02155a08;

    if ((long long)direction.x * direction.x +
            (long long)direction.y * direction.y +
            (long long)direction.z * direction.z >=
        0x10) {
        Vector3_MaybeNormalize(&direction, &direction);
    }

    VecFx32_CrossProduct(&data_02155a08, &direction, &cross);

    axis.y *= -1;
    rotation.x = axis.x;
    rotation.y = axis.y;
    rotation.z = axis.z;

    obj->f68 = 0x1000;
    obj->f50 = rotation.x;
    obj->f52 = rotation.y;
    obj->f54 = rotation.z;

    VecFx32_AddScale1(data_02165964, &direction, &hd->f9c, &target);
    target.y += data_02165968 + FX_Mul(hd->f15c.y, data_02165960);

    obj->f28 = target.x + (*obj->f20)->f4;
    obj->f2c = target.y + (*obj->f20)->f8;
    obj->f30 = target.z + (*obj->f20)->fc;
}
