// PURPOSE: Builds an object's orientation matrix and installs its update callback.
// The object probably stores three orientation vectors together at offset 0x94.
// It normalizes the first vector when it is long enough, derives the third vector,
// and applies a shared orientation transform before enabling the update callback.

typedef unsigned char u8;
typedef int fx32;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct MtxFx33 {
    fx32 m[3][3];
} MtxFx33;

typedef struct Object020ff344 {
    u8 unused_000[0x74];
    int flags_074;
    u8 unused_078[0x1c];
    MtxFx33 orientation_094;
    u8 unused_0b8[0x68];
    void *field_120;
} Object020ff344;

extern MtxFx33 data_0217c600;
extern void func_020ff438(void);
extern void Vector3_MaybeNormalize(VecFx32 *vector, VecFx32 *out);
extern void Vector3_Cross(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void MTX_Concat33(const MtxFx33 *left, const MtxFx33 *right,
                         MtxFx33 *out);

void func_020ff344(Object020ff344 *object)
{
    if ((long long)object->orientation_094.m[0][0]
            * object->orientation_094.m[0][0]
        + (long long)object->orientation_094.m[0][1]
            * object->orientation_094.m[0][1]
        + (long long)object->orientation_094.m[0][2]
            * object->orientation_094.m[0][2] >= 0x10) {
        Vector3_MaybeNormalize((VecFx32 *)&object->orientation_094,
                               (VecFx32 *)&object->orientation_094);
    }

    Vector3_Cross((VecFx32 *)&object->orientation_094,
                  (VecFx32 *)&object->orientation_094.m[1],
                  (VecFx32 *)&object->orientation_094.m[2]);
    MTX_Concat33(&data_0217c600, &object->orientation_094,
                 &object->orientation_094);

    if ((object->flags_074 & 0x180000) == 0) {
        object->field_120 = func_020ff438;
    }
}
