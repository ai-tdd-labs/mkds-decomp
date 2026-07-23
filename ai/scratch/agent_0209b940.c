// PURPOSE: Sets the polygon ID on every model part owned by this map object.
// The object probably contains optional material, model, and collision records.
// The ID is stored in each record when that record is present.

typedef unsigned int u32;
typedef unsigned short u16;

typedef struct ModelBlock ModelBlock;

typedef struct PolygonMaterial {
    char _00[0x14];
    u32 flags;
} PolygonMaterial;

typedef struct ModelOwner {
    char _00[4];
    ModelBlock *model;
} ModelOwner;

typedef struct PolygonCollision {
    char _00[0x6c];
    u16 polygonId;
} PolygonCollision;

typedef struct StructMapObject {
    char _00[0x0c];
    PolygonMaterial *material;
    ModelOwner *modelOwner;
    PolygonCollision *collision;
} StructMapObject;

extern void ModelBlock_SetPolygonId(ModelBlock *model, int arg1);

void StructMapObject_MaybeSetPolygonId(StructMapObject *object, int polygonId)
{
    if (object->material != 0) {
        object->material->flags &= 0xc0ffffff;
        object->material->flags |= polygonId << 24;
    }

    if (object->modelOwner != 0) {
        ModelBlock_SetPolygonId(object->modelOwner->model, polygonId);
    }

    if (object->collision != 0) {
        object->collision->polygonId = polygonId;
    }
}
