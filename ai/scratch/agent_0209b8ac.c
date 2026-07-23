// PURPOSE: Enables or disables a model flag on a map object.
/*
 * Updates bit 0x8000 on the optional linked sub-object, then probably
 * forwards the same state to its model when the model reference exists.
 */

typedef struct ModelBlock ModelBlock;

typedef struct StructMapObject_Sub {
    char pad_0x00[0x14];
    unsigned int flags; /* 0x14 */
} StructMapObject_Sub;

typedef struct StructMapObject_ModelRef {
    char pad_0x00[0x04];
    ModelBlock *model; /* 0x04 */
} StructMapObject_ModelRef;

typedef struct StructMapObject {
    char pad_0x00[0x0c];
    StructMapObject_Sub *sub;          /* 0x0c */
    StructMapObject_ModelRef *modelRef; /* 0x10 */
} StructMapObject;

extern void Maybe_helper_013044(ModelBlock *model, int arg1);

void StructMapObject_SomeFn_7(StructMapObject *object, int enabled)
{
    StructMapObject_Sub *sub = object->sub;

    if (sub != 0) {
        if (enabled != 0) {
            sub->flags |= 0x8000;
        } else {
            sub->flags &= ~0x8000;
        }
    }

    if (object->modelRef != 0) {
        Maybe_helper_013044(object->modelRef->model, enabled);
    }
}
