// PURPOSE: Tests whether a point lies inside an oriented volume.
// The first argument is the point and the second describes the volume.
// It projects the point's offset onto three axes and checks their limits.
// The middle axis is probably one-sided while the other two are centered.

typedef int fx32;
typedef long long fx64;

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
} OrientedVolume;

extern fx32 Vector3_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void VecFx32_Subtract(const VecFx32 *a, const VecFx32 *b,
                             VecFx32 *out);

int func_02041a70(const VecFx32 *point, const OrientedVolume *volume)
{
    VecFx32 offset;
    fx32 dot;
    fx32 limit;

    VecFx32_Subtract(point, &volume->origin, &offset);

    dot = Vector3_DotProduct(&offset, &volume->axis1);
    limit = (fx32)(((fx64)volume->extent1 * 0x64000 + 0x800) >> 12);
    if (dot > limit || dot < 0)
        return 0;

    dot = Vector3_DotProduct(&offset, &volume->axis0);
    limit = (fx32)(((fx64)volume->extent0 * 0x32000 + 0x800) >> 12);
    if (dot < -limit || dot > limit)
        return 0;

    dot = Vector3_DotProduct(&offset, &volume->axis2);
    limit = (fx32)(((fx64)volume->extent2 * 0x32000 + 0x800) >> 12);
    if (dot < -limit || dot > limit)
        return 0;

    return 1;
}
