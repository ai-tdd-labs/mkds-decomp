// PURPOSE: Moves a rolling obstacle toward its target until its lifetime ends.
// The object stores its position, horizontal velocity, target, and stopping radius.
// It accelerates while outside the target radius and probably applies drag at high speed.
// After 180 ticks, it disables its active state and marks itself as finished.

typedef int fx32;
typedef long long fx64;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct MovingObject {
    char pad_000[0x4];
    VecFx32 position_004;
    VecFx32 velocity_010;
    char pad_01c[0x84 - 0x1c];
    unsigned int timer_084;
    char pad_088[0x90 - 0x88];
    unsigned short state_090;
    unsigned short finished_092;
    char pad_094[0xa0 - 0x94];
    VecFx32 target_0a0;
    char pad_0ac[0x1fc - 0xac];
    fx32 stoppingRadius_1fc;
} MovingObject;

extern void VecFx32_Subtract(const VecFx32 *a, const VecFx32 *b,
                             VecFx32 *out);

#define FX_MUL(a, b) ((fx32)(((fx64)(a) * (b)) >> 12))

void func_020dc474(MovingObject *object)
{
    VecFx32 difference;
    fx32 *velocityX;
    fx32 *velocityZ;

    if ((fx64)(object->position_004.x - object->target_0a0.x)
                * (object->position_004.x - object->target_0a0.x)
            + (fx64)(object->position_004.z - object->target_0a0.z)
                * (object->position_004.z - object->target_0a0.z)
        >= (fx64)object->stoppingRadius_1fc * object->stoppingRadius_1fc) {
        fx64 speedLimit = 0x1000000LL;

        VecFx32_Subtract(&object->target_0a0, &object->position_004,
                         &difference);

        object->velocity_010.x += FX_MUL(difference.x, 4);
        object->velocity_010.z += FX_MUL(difference.z, 4);

        velocityX = &object->velocity_010.x;
        velocityZ = &object->velocity_010.z;

        if ((fx64)object->velocity_010.x * object->velocity_010.x
                + (fx64)object->velocity_010.z * object->velocity_010.z
            >= speedLimit) {
            /* Separate lvalue and source reads preserve the observed reloads. */
            *velocityX = *velocityX
                - FX_MUL(object->velocity_010.x, 0x199);
            *velocityZ = *velocityZ
                - FX_MUL(object->velocity_010.z, 0x199);
        }

        object->position_004.x += object->velocity_010.x;
        object->position_004.z += object->velocity_010.z;
    }

    if (object->timer_084 >= 0xb4) {
        object->state_090 = 0;
        object->finished_092 = 1;
    }
}
