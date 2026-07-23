// PURPOSE: Checks whether an object can react to a transformed vector.

typedef int fx32;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct MtxFx33 {
    fx32 m[9];
} MtxFx33;

typedef struct Object {
    void *unk_00;
    VecFx32 position;
    char unk_10[0x18];
    MtxFx33 matrix;
    char unk_4c[0xd4];
    int unk_120;
    char unk_124[0xc];
    void *unk_130;
} Object;

typedef struct ObjectContext {
    Object *object;
    VecFx32 transformed;
    VecFx32 transformed_10;
} ObjectContext;

typedef struct InputData {
    int unk_00;
    int unk_04;
} InputData;

extern void MTX_MultVec33(VecFx32 *dst, const MtxFx33 *mtx, const VecFx32 *src);
extern void VecFx32_Add(VecFx32 *dst, const VecFx32 *a, const VecFx32 *b);

int func_020e04b0(ObjectContext *context, VecFx32 *vector, InputData *input)
{
    Object *object = context->object;

    if (object == 0) {
        goto return_zero;
    }

    MTX_MultVec33(&context->transformed, &object->matrix, vector);
    VecFx32_Add(&object->position, vector, vector);

    if (object->unk_130 == 0) {
        goto return_zero;
    }

    MTX_MultVec33(&context->transformed_10, &object->matrix, (VecFx32 *)input);
    if (input->unk_04 < object->unk_120) {
        return 1;
    }

return_zero:
    return 0;
}
