// PURPOSE: Updates an object's position from a transformed vector.
// The first argument points to a context containing the object and a vector.
// The vector is probably transformed by the object's matrix, then added to
// the supplied vector before the object's position is updated.

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
} Object;

typedef struct ObjectContext {
    Object *object;
    VecFx32 transformed;
} ObjectContext;

extern void MTX_MultVec33(VecFx32 *dst, const MtxFx33 *mtx, const VecFx32 *src);
extern void VecFx32_Add(VecFx32 *dst, const VecFx32 *a, const VecFx32 *b);

void func_020e0538(ObjectContext *context, VecFx32 *vector)
{
    Object *object = context->object;

    if (object == 0) {
        return;
    }

    MTX_MultVec33(&context->transformed, &object->matrix, vector);
    VecFx32_Add(&object->position, vector, vector);
}
