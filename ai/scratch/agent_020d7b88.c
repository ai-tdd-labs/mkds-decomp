/* PURPOSE: Converts a surface normal into an upright rotation quaternion.
 * normal supplies a fixed-point direction and rotation receives x, y, z, w.
 * The formula probably assumes that normal is already normalized and is not
 * pointing exactly downward, because that would make the divisor zero. */

typedef int fx32;

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

extern fx32 FX_Sqrt(fx32 value);
extern void FX_DivAsync(fx32 numerator, fx32 denominator);
extern fx32 FX_GetDivResult(void);

void func_020d7b88(const VecFx32 *normal, Quaternion *rotation)
{
    fx32 scale = FX_Sqrt((normal->y + 0x1000) << 1);

    FX_DivAsync(normal->z, scale);
    rotation->y = 0;
    rotation->x = FX_GetDivResult();

    FX_DivAsync(-normal->x, scale);
    rotation->w = scale >> 1;
    rotation->z = FX_GetDivResult();
}
