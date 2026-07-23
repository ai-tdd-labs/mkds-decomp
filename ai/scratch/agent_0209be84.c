/*
PURPOSE: Creates a map object from a model file.
The first argument is probably an owning map object whose loaded flag is set.
The second argument names the model resource to load.
The returned wrapper owns an allocated model and keeps the resource buffer.
*/

typedef unsigned int u32;

typedef struct Vec3 {
    int x;
    int y;
    int z;
} Vec3;

typedef struct MapObjectOwner {
    unsigned char unknown_00[0x18];
    int modelLoaded;
} MapObjectOwner;

typedef struct MapModelObject {
    Vec3 position;
    u32 unknown_0c;
    void *model;
    u32 unknown_14;
    void *fileBuffer;
    unsigned char unknown_1c[0x10];
} MapModelObject;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void *FormatFindMapObjFileBuffer_from_thumb(void *modelName);
extern void Model_CreateFromNsbmd(void *model, void *fileBuffer);
extern void Model_SetEmi(void *model, int emission);
extern void StructML_SomeFn_8(void *model, int value);

extern const Vec3 data_021565c4;

MapModelObject *CreateMapObjectFromModel_from_thumb(
    MapObjectOwner *owner, void *modelName)
{
    MapModelObject *object;

    object = (MapModelObject *)Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0x2c);

    if (owner != 0) {
        owner->modelLoaded = 1;
    }

    object->fileBuffer = FormatFindMapObjFileBuffer_from_thumb(modelName);
    object->model = Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0x6c);

    Model_CreateFromNsbmd(object->model, object->fileBuffer);
    Model_SetEmi(object->model, 0x294a);
    StructML_SomeFn_8(object->model, 2);

    object->position = data_021565c4;
    return object;
}
