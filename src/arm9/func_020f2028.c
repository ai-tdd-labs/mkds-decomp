// PURPOSE: Updates an object's vertical movement for its current state.
// The object supplies a movement vector, state flags, and a fallback adjustment vector.
// Special states subtract a quarter-strength adjustment from the movement.
// Otherwise the vertical component is damped or clamped according to the object's flags.

typedef int fx32;
typedef long long fx64;

typedef struct {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct {
    char pad00[0x5c];
    VecFx32 movement;
    char pad68[0x74 - 0x68];
    unsigned int movementFlags;
    char pad78[0xf0 - 0x78];
    VecFx32 adjustment;
    unsigned int stateFlags;
} Object;

extern void VecFx32_Subtract(const VecFx32 *a, const VecFx32 *b,
                             VecFx32 *out);

void func_020f2028(Object *object)
{
    VecFx32 quarterAdjustment;
    VecFx32 *movement = &object->movement;

    if (object->stateFlags & 0x1e34ef) {
        quarterAdjustment.x = object->adjustment.x >> 2;
        quarterAdjustment.y = object->adjustment.y >> 2;
        quarterAdjustment.z = object->adjustment.z >> 2;
        VecFx32_Subtract(movement, &quarterAdjustment, movement);
        return;
    }

    if (movement->y > 0) {
        movement->y -= 0x6b8;

        if (!(object->movementFlags & 0x20000))
            return;

        if (movement->y > 0xa000) {
            movement->y >>= 3;
            return;
        }

        movement->y = (fx32)(((fx64)movement->y * 0xe66LL) >> 12);
        return;
    }

    movement->y -= 0x333;
    if (movement->y >= -0xa000)
        return;

    if (object->movementFlags & 0x20000)
        movement->y = -0xa000;
}
