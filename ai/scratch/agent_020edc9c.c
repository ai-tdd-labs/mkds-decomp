// PURPOSE: Builds a usable travel direction and updates the remaining distance.
// The object probably supplies the movement, facing, and fallback vectors.
// The scalar arguments adjust the returned distance and direction scale.
// The final argument receives the normalized direction when it is usable.

typedef int fx32;
typedef long long fx64;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct DirectionSource {
    char pad_000[0x48];
    unsigned int flags_048;
    char pad_04c[0x1fc - 0x4c];
    VecFx32 reference_1fc;
} DirectionSource;

typedef struct MovementObject {
    char pad_000[0x10];
    DirectionSource *source_010;
    char pad_014[0x44 - 0x14];
    VecFx32 direction_044;
    char pad_050[0x6c - 0x50];
    VecFx32 movement_06c;
    char pad_078[0x80 - 0x78];
    int use_alternate_080;
} MovementObject;

extern fx32 VecFx32_Norm(const VecFx32 *vector);
extern void VecFx32_AddScale1(fx32 scale, const VecFx32 *direction,
                              const VecFx32 *base, VecFx32 *out);
extern void Vector3_MaybeNormalize(const VecFx32 *in, VecFx32 *out);

#define FX_MUL(a, b) ((fx32)(((fx64)(a) * (b)) >> 12))

fx32 func_020edc9c(MovementObject *object, fx32 distance, fx32 factor,
                    fx32 scale, VecFx32 *out)
{
    VecFx32 direction;
    fx32 length;

    length = VecFx32_Norm(&object->movement_06c);

    if (object->use_alternate_080 != 0) {
        distance += FX_MUL(length, factor);
        VecFx32_AddScale1(scale, &object->direction_044,
                          &object->movement_06c, &direction);
    } else if ((fx64)object->source_010->reference_1fc.x
                           * object->source_010->reference_1fc.x
                       + (fx64)object->source_010->reference_1fc.y
                           * object->source_010->reference_1fc.y
                       + (fx64)object->source_010->reference_1fc.z
                           * object->source_010->reference_1fc.z >= 0x10) {
        distance += FX_MUL(length, factor);
        VecFx32_AddScale1(scale, &object->direction_044,
                          &object->source_010->reference_1fc, &direction);
    } else {
        distance -= length;
        direction = object->direction_044;
    }

    if ((object->source_010->flags_048 & 1) == 0)
        direction.y = 0;

    if ((fx64)direction.x * direction.x
            + (fx64)direction.y * direction.y
            + (fx64)direction.z * direction.z >= 0x10) {
        Vector3_MaybeNormalize(&direction, out);
    }

    return distance;
}
