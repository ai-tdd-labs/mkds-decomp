// PURPOSE: Tests a point against the collision volume selected by its mode.
// The first argument is the point to test.
// The second argument supplies the volume origin, axes, extents, and mode.
// Mode zero uses the regular volume test; mode one probably tests a rounded end.

typedef int fx32;
typedef long long fx64;
typedef unsigned char u8;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct OrientedVolume {
    VecFx32 origin;
    fx32 extent0;
    fx32 extent1;
    fx32 extent2;
    VecFx32 axis0;
    VecFx32 axis1;
    VecFx32 axis2;
    u8 pad3c[6];
    u8 mode;
} OrientedVolume;

extern int func_02041a70(const VecFx32 *point,
                         const OrientedVolume *volume);
extern fx32 Vector3_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void VecFx32_Subtract(const VecFx32 *a, const VecFx32 *b,
                             VecFx32 *out);

#define FX_MUL(a, b) ((fx32)(((fx64)(a) * (b) + 0x800) >> 12))

int func_02041944(const VecFx32 *point, const OrientedVolume *volume)
{
    VecFx32 offset;
    int inside = 0;

    switch (volume->mode) {
    case 0:
        inside = func_02041a70(point, volume);
        break;

    case 1: {
        fx32 radius;
        fx32 projection2;
        fx32 projection0;

        VecFx32_Subtract(point, &volume->origin, &offset);

        if (Vector3_DotProduct(&offset, &volume->axis1) <=
            (fx32)(((fx64)volume->extent1 * 0x32000 + 0x800) >> 12)) {
            projection0 = Vector3_DotProduct(&offset, &volume->axis0) >> 4;
            projection2 = Vector3_DotProduct(&offset, &volume->axis2) >> 4;
            radius =
                (fx32)(((fx64)volume->extent0 * 0x32000 + 0x800) >> 12) >> 4;

            if (FX_MUL(radius, radius) >=
                FX_MUL(projection0, projection0) +
                    FX_MUL(projection2, projection2)) {
                inside = 1;
            }
        }
        break;
    }
    }

    return inside;
}
