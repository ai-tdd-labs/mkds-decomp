/* Builds a clamped offset vector between two points a and b (fx32 vectors).
 * out = a - b, but the y component is first zeroed so the horizontal (x,z)
 * length is measured. If that horizontal length^2 >= 0x10 the direction is
 * normalized into a temp, and the x/z components are pushed inward by 'scale'
 * along the normalized direction. The y difference is then folded against
 * 'limit' (limit - dy if dy>0, else -(limit + dy)). Finally, if |y| is smaller
 * than the horizontal length, x and z are clamped to +/- |y|, and y is zeroed.
 * Probably a "keep offset inside a cone/box" helper for camera or AI targeting.
 * args: a, b = points; scale, limit = fx32 scalars; out = result vector. */

typedef int fx32;
typedef long long fx64;

typedef struct { fx32 x, y, z; } VecFx32;

extern void Vector3_MaybeNormalize(VecFx32 *v, VecFx32 *dst);

void func_020eb2a0(VecFx32 *a, VecFx32 *b, fx32 scale, fx32 limit, VecFx32 *out) {
    VecFx32 dir;   /* normalized horizontal direction (stack temp) */
    fx64 mag;

    out->x = a->x - b->x;
    out->y = 0;
    out->z = a->z - b->z;

    /* horizontal length^2 (y is 0 here); order y,x,z matches the smull/smlal */
    mag = (fx64)out->x * out->x + (fx64)out->y * out->y + (fx64)out->z * out->z;
    if (mag >= 0x10)
        Vector3_MaybeNormalize(out, &dir);

    /* push x/z inward: out = dir*scale (fx mul, >>12) - out */
    out->x = (fx32)(((fx64)dir.x * scale) >> 12) - out->x;
    out->z = (fx32)(((fx64)dir.z * scale) >> 12) - out->z;

    out->y = a->y - b->y;
    if (out->y > 0)
        out->y = limit - out->y;
    else
        out->y = -(limit + out->y);

    /* clamp x,z to +/- |y| when the horizontal part exceeds |y| */
    if ((fx64)out->x * out->x + (fx64)out->z * out->z > (fx64)out->y * out->y) {
        fx32 ay = out->y;
        if (ay <= 0)
            ay = -ay;
        if (out->x > ay)
            out->x = ay;
        else if (out->x < -ay)
            out->x = -ay;
        if (out->z > ay)
            out->z = ay;
        else if (out->z < -ay)
            out->z = -ay;
    }

    out->y = 0;
}
