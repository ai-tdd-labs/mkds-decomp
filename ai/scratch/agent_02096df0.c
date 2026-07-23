/*
 * Collision test against a cylindrical/spherical object.
 * args: obj (r0), point p (r1), margin (r2, fx32), out push-out vector (r3).
 * Computes diff = p - obj->pos; rejects if diff.y >= obj->height + margin
 * or |diff| >= obj->radius + margin (returns 0). Otherwise, depending on
 * obj->type, writes either a zero vector or diff normalized and scaled by
 * the penetration depth into out, and returns 1.
 */

typedef int fx32;
typedef long long s64;
typedef struct { fx32 x, y, z; } VecFx32;

typedef struct {
    int unk0;                    /* 0x00 */
    VecFx32 pos;                 /* 0x04 */
    char pad10[0x58 - 0x10];
    fx32 radius;                 /* 0x58 */
    char pad5c[0xa0 - 0x5c];
    fx32 height;                 /* 0xa0 (probably vertical extent) */
    char pada4[0xb0 - 0xa4];
    int type;                    /* 0xb0 */
} Obj;

extern void VecFx32_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VecFx32_Norm(const VecFx32 *v);
extern void Vector3_MaybeNormalize(VecFx32 *dst, VecFx32 *src);

int func_02096df0(Obj *obj, const VecFx32 *p, fx32 margin, VecFx32 *out)
{
    VecFx32 diff;
    fx32 dist;

    VecFx32_Subtract(p, &obj->pos, &diff);
    if (diff.y >= obj->height + margin) {
        return 0;
    }
    dist = VecFx32_Norm(&diff);
    if (dist >= obj->radius + margin) {
        return 0;
    }
    if (obj->type == 1) {
        out->x = 0;
        out->y = 0;
        out->z = 0;
        return 1;
    }
    if (obj->type == 4 || (obj->type == 5 && obj->height > 0x7800)) {
        /* normalize diff only if its squared magnitude is big enough */
        if ((s64)diff.x * diff.x + (s64)diff.y * diff.y + (s64)diff.z * diff.z >= 16) {
            Vector3_MaybeNormalize(&diff, &diff);
        }
        dist = (obj->radius + margin) - dist; /* penetration depth, reuses r4 */
        out->x = (fx32)(((s64)diff.x * dist) >> 12);
        out->y = (fx32)(((s64)diff.y * dist) >> 12);
        out->z = (fx32)(((s64)diff.z * dist) >> 12);
        return 1;
    }
    out->x = 0;
    out->y = 0;
    out->z = 0;
    return 1;
}
