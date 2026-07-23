// PURPOSE: Adjusts a movement direction so it follows a surface.
// direction is the requested movement, normal is probably the surface normal,
// and out receives the adjusted direction. Nearly horizontal surfaces reverse
// the direction; otherwise the result is normalized when it is long enough.

typedef int fx32;
typedef long long fx64;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

#define FX_MUL(a, b) ((fx32)(((fx64)(a) * (fx32)(b)) >> 12))

extern void FX_Div(void *a0);
extern void Vector3_MaybeNormalize(const VecFx32 *in, VecFx32 *out);

void func_020f2a6c(const VecFx32 *direction, const VecFx32 *normal, VecFx32 *out)
{
    if (normal->y * normal->y < 0x10) {
        out->x = -direction->x;
        out->y = -direction->y;
        out->z = -direction->z;
        return;
    }

    out->x = normal->x >> 2;
    out->y = normal->y >> 2;
    out->z = normal->z >> 2;

    out->x = direction->x - out->x;
    out->z = direction->z - out->z;

    /* Keep the two fixed-point products together in the ROM's add tree. */
    out->y = -((FX_MUL(direction->x, normal->x)
              + FX_MUL(direction->z, normal->z))
             + out->y);
    out->y = ((fx32 (*)(fx32, fx32))FX_Div)(out->y, normal->y);

    if ((fx64)out->x * out->x
        + (fx64)out->y * out->y
        + (fx64)out->z * out->z >= 0x10)
        Vector3_MaybeNormalize(out, out);
}
