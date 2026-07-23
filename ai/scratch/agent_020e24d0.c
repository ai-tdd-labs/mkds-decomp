// PURPOSE: Builds a ground-facing rotation and updates the object's movement state.
// The first argument is the object being updated and the second is a target position.
// It derives a normal from two facing vectors, normalizes it when long enough,
// converts that normal to a quaternion, and advances the object's timers and flags.

typedef int fx32;
typedef long long fx64;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct Quaternion {
    fx32 x;
    fx32 y;
    fx32 z;
    fx32 w;
} Quaternion;

typedef struct Object {
    unsigned short f0;
    unsigned short flags;
    VecFx32 position;
    char pad10[4];
    fx32 f14;
    char pad18[0x28 - 0x18];
    VecFx32 direction28;
    char pad34[0x40 - 0x34];
    VecFx32 direction40;
    char pad4c[0xc4 - 0x4c];
    Quaternion rotation;
    char padD4[0xfe - 0xd4];
    signed short timer;
    char pad100[0x118 - 0x100];
    fx32 height;
    char pad11c[0x152 - 0x11c];
    unsigned short duration;
} Object;

extern void VecFx32_Subtract(const VecFx32 *a, const VecFx32 *b,
                             VecFx32 *out);
extern fx32 VecFx32_CrossProduct_0(const VecFx32 *a, const VecFx32 *b);
extern void Vector3_MaybeNormalize(VecFx32 *a, VecFx32 *out);
extern void func_020d7b88(const VecFx32 *normal, Quaternion *rotation);
extern unsigned short data_02158a50;

void func_020e24d0(Object *object, const VecFx32 *target)
{
    VecFx32 normal;
    fx32 cross28;
    fx32 cross40;
    fx32 value;

    normal = object->position;
    VecFx32_Subtract(&normal, target, &normal);

    cross28 = VecFx32_CrossProduct_0(&object->direction28, &normal);
    cross40 = VecFx32_CrossProduct_0(&object->direction40, &normal);

    normal.x = (cross28 > 0 ? object->direction28.x
                            : -object->direction28.x) * 2;
    normal.x += cross40 > 0 ? object->direction40.x
                            : -object->direction40.x;
    normal.z = (cross28 > 0 ? object->direction28.z
                            : -object->direction28.z) * 2;
    normal.z += cross40 > 0 ? object->direction40.z
                            : -object->direction40.z;
    normal.y = ((object->height - 0x14000) >> 4) + 0x2000;

    if ((fx64)normal.x * normal.x + (fx64)normal.y * normal.y
        + (fx64)normal.z * normal.z >= 0x10) {
        Vector3_MaybeNormalize(&normal, &normal);
    }

    func_020d7b88(&normal, &object->rotation);
    object->duration = 0x384;

    if (object->timer > 0xf || (value = object->f14) <= 0) {
        value = 0;
    }
    object->f14 = value + 0x7000;

    object->flags |= data_02158a50;
    object->timer = 0x14;
}
