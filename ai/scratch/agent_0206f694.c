// PURPOSE: Smooths an object's velocity and stops tiny residual movement.
// The object, state flags, requested velocity, and an adjustment are inputs.
// A nonzero request is approached directly, while a zero request applies drag.
// The vertical component is probably accumulated separately from planar motion.

typedef int fx32;
typedef long long fx64;
typedef unsigned int u32;
typedef unsigned short u16;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct MotionObject {
    char padding_000[0x44];
    u32 flags_044;
    char padding_048[0x1fc - 0x48];
    VecFx32 velocity_1fc;
    char padding_208[0x236 - 0x208];
    u16 adjustment_236;
    char padding_238[0x260 - 0x238];
    fx32 accumulated_y_260;
} MotionObject;

extern const VecFx32 data_02165554;
extern const VecFx32 data_02154f94;
extern void VecFx32_Subtract(const VecFx32 *a, const VecFx32 *b,
                             VecFx32 *out);
extern void VecFx32_AddScale1(fx32 scale, const VecFx32 *direction,
                              const VecFx32 *base, VecFx32 *out);

void func_0206f694(MotionObject *object, u32 state,
                   const VecFx32 *requested_velocity, int adjustment)
{
    VecFx32 difference;
    VecFx32 drag;

    if (state & 0x40000000) {
        object->flags_044 |= 0x40000;
        object->adjustment_236 += adjustment;
    } else if (state & 0x1e34ef) {
        object->velocity_1fc.y = 0;
    }

    if (requested_velocity->x | requested_velocity->y
        | requested_velocity->z) {
        VecFx32_Subtract(requested_velocity, &object->velocity_1fc,
                         &difference);

        if ((fx64)difference.x * difference.x
                + (fx64)difference.y * difference.y
                + (fx64)difference.z * difference.z
            < (fx64)0x1000000) {
            object->velocity_1fc = *requested_velocity;
        } else {
            VecFx32_AddScale1(0x199, &difference, &object->velocity_1fc,
                              &object->velocity_1fc);
        }

        object->accumulated_y_260 += object->velocity_1fc.y;
        object->velocity_1fc.y = 0;
        return;
    }

    drag = data_02165554;
    object->velocity_1fc.x =
        (fx32)(((fx64)object->velocity_1fc.x * drag.x) >> 12);
    object->velocity_1fc.y =
        (fx32)(((fx64)object->velocity_1fc.y * drag.y) >> 12);
    object->velocity_1fc.z =
        (fx32)(((fx64)object->velocity_1fc.z * drag.z) >> 12);

    if ((fx64)object->velocity_1fc.x * object->velocity_1fc.x
            + (fx64)object->velocity_1fc.y * object->velocity_1fc.y
            + (fx64)object->velocity_1fc.z * object->velocity_1fc.z
        < (fx64)0xa429) {
        object->velocity_1fc = data_02154f94;
    }
}
