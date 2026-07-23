// PURPOSE: Initializes an object's transform and movement settings.
// The object pointer supplies its position, dimensions, and source matrix.
// This probably prepares derived fixed-point bounds and a starting offset.

typedef unsigned char u8;
typedef unsigned short u16;
typedef int fx32;
typedef long long fx64;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct MtxFx33 {
    fx32 m[3][3];
} MtxFx33;

typedef struct ObjectState {
    u16 field_000;
    u16 flags_002;
    VecFx32 position_004;
    VecFx32 velocity_010;
    VecFx32 dimensions_01c;
    MtxFx33 source_matrix_028;
    u8 pad_04c[0x54];
    MtxFx33 matrix_0a0;
    u8 pad_0c4[0x24];
    VecFx32 position_0e8;
    VecFx32 offset_position_0f4;
    fx32 field_100;
    fx32 field_104;
    fx32 field_108;
    fx32 field_10c;
    fx32 field_110;
    fx32 field_114;
    fx32 field_118;
    fx32 field_11c;
    fx32 field_120;
    fx32 field_124;
    fx32 field_128;
    fx32 field_12c;
    fx32 field_130;
    fx32 field_134;
    fx32 field_138;
    fx32 field_13c;
} ObjectState;

extern fx64 Multiply64(fx64 left, fx64 right);
extern void VecFx32_AddScale1(fx32 scale, const VecFx32 *direction,
                              const VecFx32 *base, VecFx32 *out);
extern u16 data_0215a030;

void func_020ff97c(ObjectState *object)
{
    object->matrix_0a0 = object->source_matrix_028;

    object->field_124 = 0;
    object->field_128 = 0;
    object->field_12c = 0;
    object->field_130 = 0;

    object->field_100 =
        (fx32)(Multiply64(object->dimensions_01c.x, 0x190000) >> 12);
    object->field_104 =
        (fx32)(Multiply64(object->dimensions_01c.y, 0x64000) >> 12) >> 1;
    object->field_108 =
        (fx32)(Multiply64(object->dimensions_01c.z, 0xaf000) >> 12);
    object->field_10c =
        (fx32)(Multiply64(object->dimensions_01c.z, 0xaf000) >> 12);

    object->field_110 = 0;
    object->field_114 = 1;
    object->field_118 = 0;
    object->field_11c = 0;
    object->field_120 = 0x800;

    object->position_0e8 = object->position_004;
    object->velocity_010.x = 0;
    object->velocity_010.y = 0;
    object->velocity_010.z = 0;

    VecFx32_AddScale1(-object->field_104,
                      (VecFx32 *)&object->source_matrix_028.m[1][0],
                      &object->position_004, &object->offset_position_0f4);

    object->field_134 = 0;
    object->field_138 = 0;
    object->field_13c = 1;
    object->flags_002 |= data_0215a030;
}
