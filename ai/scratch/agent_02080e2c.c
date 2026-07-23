// PURPOSE: Checks whether a point lies inside an object's horizontal range.
// The first argument supplies an object containing a position and range value.
// The function subtracts the supplied position, ignores vertical distance, and
// probably returns one when the remaining horizontal distance is in range.

typedef int fx32;

typedef struct {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct {
    char padding[0x20];
    const VecFx32 *position;
    fx32 range;
} RangeObject;

typedef struct {
    RangeObject *object;
} RangeCheck;

extern void VecFx32_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

int func_02080e2c(RangeCheck *check, const VecFx32 *position)
{
    VecFx32 delta;
    int zero = 0;
    fx32 range = check->object->range;

    VecFx32_Subtract(check->object->position, position, &delta);
    return (long long)zero * zero + (long long)delta.x * delta.x
               + (long long)delta.z * delta.z
           < (long long)range * range;
}
