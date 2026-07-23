/*
 * Tests whether a point lies within a directional distance band of an object.
 * The function probably produces a normalized, scaled direction in `out`.
 * It rejects points outside the vertical or radial limits and clears `out` for
 * the special and unsupported modes.
 */
typedef int fx32;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct Unk02096df0 {
    char pad0[4];
    VecFx32 origin;
    char pad10[0x48];
    fx32 radius;
    char pad5c[0x44];
    fx32 vertical_limit;
    char padA4[0x0c];
    int mode;
} Unk02096df0;

extern void VecFx32_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VecFx32_Norm(const VecFx32 *v);
extern void Vector3_MaybeNormalize(const VecFx32 *in, VecFx32 *out);

int func_02096df0(Unk02096df0 *self, const VecFx32 *point, fx32 extra, VecFx32 *out)
{
    VecFx32 delta;
    fx32 distance;
    fx32 scale;

    VecFx32_Subtract(point, &self->origin, &delta);
    if (delta.y >= self->vertical_limit + extra)
        return 0;

    distance = VecFx32_Norm(&delta);
    if (distance >= self->radius + extra)
        return 0;

    if (self->mode == 1) {
        out->x = 0;
        out->y = 0;
        out->z = 0;
        return 1;
    }

    if (self->mode == 4 || (self->mode == 5 && self->vertical_limit > 0x7800)) {
        if ((long long)delta.x * delta.x + (long long)delta.y * delta.y + (long long)delta.z * delta.z >= 0x10)
            Vector3_MaybeNormalize(&delta, &delta);

        scale = self->radius + extra - distance;
        out->x = (fx32)(((long long)delta.x * scale) >> 12);
        out->y = (fx32)(((long long)delta.y * scale) >> 12);
        out->z = (fx32)(((long long)delta.z * scale) >> 12);
        return 1;
    }

    out->x = 0;
    out->y = 0;
    out->z = 0;
    return 1;
}
