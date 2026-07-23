// PURPOSE: Checks whether a point lies within a horizontal distance limit.
// The owner supplies a reference position and a vertical distance limit.
// It probably reports whether the horizontal displacement is smaller than that limit.

typedef int fx32;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct DistanceCheck {
    void *unused0;
    char padding[0x14];
    VecFx32 *position;
    fx32 limit;
} DistanceCheck;

extern void VecFx32_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

int func_02080c64(DistanceCheck **check, const VecFx32 *point)
{
    VecFx32 delta;
    int result;

    VecFx32_Subtract((*check)->position, point, &delta);
    result = 0;
    if ((long long)delta.x * delta.x + (long long)delta.z * delta.z <
        (long long)(*check)->limit * (*check)->limit) {
        result = 1;
    }
    return result;
}
