// PURPOSE: Builds a scaled offset vector between two points.
// Subtracts b from a into out, probably normalizes that direction when it is long enough,
// then replaces out with the scaled direction minus the original offset.
// Arguments are two input fx32 vectors, a fx32 scale, and the output vector.

typedef int fx32;
typedef long long s64;

typedef struct {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

extern void VecFx32_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void Vector3_MaybeNormalize(VecFx32 *dst, VecFx32 *src);

void func_020eb3f0(const VecFx32 *a, const VecFx32 *b, fx32 scale, VecFx32 *out)
{
    VecFx32 direction;

    VecFx32_Subtract(a, b, out);
    if ((s64)out->x * out->x + (s64)out->y * out->y + (s64)out->z * out->z >= 0x10) {
        Vector3_MaybeNormalize(out, &direction);
    }

    /* Fixed-point scale, preserving the temporary's stack layout. */
    direction.x = (fx32)(((s64)direction.x * scale) >> 12);
    direction.y = (fx32)(((s64)direction.y * scale) >> 12);
    direction.z = (fx32)(((s64)direction.z * scale) >> 12);
    VecFx32_Subtract(&direction, out, out);
}
