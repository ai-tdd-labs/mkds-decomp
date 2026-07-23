// PURPOSE: Updates the map object's model settings and stored value.
// The object probably owns optional render, model, and state records.
// The supplied value is copied into each record that is present.

typedef unsigned int u32;
typedef unsigned short u16;

typedef struct ModelBlock ModelBlock;

typedef struct RenderRecord {
    char _00[0x14];
    u32 flags;
} RenderRecord;

typedef struct ModelHolder {
    char _00[4];
    ModelBlock *model;
} ModelHolder;

typedef struct ValueRecord {
    char _00[0x6e];
    u16 value;
} ValueRecord;

typedef struct StructMapObject {
    char _00[0x0c];
    RenderRecord *render;
    ModelHolder *modelHolder;
    ValueRecord *valueRecord;
} StructMapObject;

extern void Maybe_helper_01308c(ModelBlock *model, int arg1);

void StructMapObject_SomeFn_6(StructMapObject *object, int value)
{
    if (object->render != 0) {
        object->render->flags &= ~0x1f0000;
        object->render->flags |= value << 16;
    }

    if (object->modelHolder != 0) {
        Maybe_helper_01308c(object->modelHolder->model, value);
    }

    if (object->valueRecord != 0) {
        object->valueRecord->value = value;
    }
}
