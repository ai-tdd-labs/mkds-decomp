// PURPOSE: Updates an object's movement direction and state flag.
// The object probably stores a direction vector at 0x130 and an output record
// at 0x140.  A shared vector is normalized into that direction when it is long
// enough, then the record is marked active.

typedef unsigned char u8;
typedef unsigned short u16;
typedef int fx32;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct Output020ff3c4 {
    u8 unused_000[0xb0];
    u16 field_0b0;
} Output020ff3c4;

typedef struct Object020ff3c4 {
    u8 unused_000[0x74];
    int flags_074;
    u8 unused_078[0xa8];
    void *field_120;
    u8 unused_124[0x0c];
    VecFx32 direction_130;
    u8 unused_13c[0x04];
    Output020ff3c4 *output_140;
} Object020ff3c4;

extern VecFx32 *data_0217bc4c;
extern void func_020ff438(void);
extern void Vector3_MaybeNormalize(VecFx32 *vector, VecFx32 *out);

int func_020ff3c4(Object020ff3c4 *object)
{
    // The source order preserves the ROM's y, x, z load sequence.
    if ((long long)data_0217bc4c->x * data_0217bc4c->x
        + (long long)data_0217bc4c->y * data_0217bc4c->y
        + (long long)data_0217bc4c->z * data_0217bc4c->z >= 0x10) {
        Vector3_MaybeNormalize(data_0217bc4c, &object->direction_130);
    }

    object->output_140->field_0b0 = 2;
    if ((object->flags_074 & 0x180000) == 0) {
        object->field_120 = func_020ff438;
    }
    return 2;
}
