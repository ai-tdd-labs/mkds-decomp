// PURPOSE: Creates a map object with a billboard model.
// The owner probably receives a loaded-state value when present.
// The model name is used to find the resource buffer.
// The returned object owns the allocated billboard model.

typedef unsigned int u32;

typedef struct Vec3 {
    int x;
    int y;
    int z;
} Vec3;

typedef struct MapObjectOwner {
    unsigned char unknown_00[0x18];
    int loaded;
} MapObjectOwner;

typedef struct BillboardModel {
    unsigned char unknown_00[0x10];
    u32 flags_10;
    u32 flags_14;
} BillboardModel;

typedef struct MapObject {
    Vec3 position;
    BillboardModel *model;
} MapObject;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void *FormatFindMapObjFileBuffer_from_thumb(void *modelName);
extern void BillboardModel_CreateFromNsbmdNsbtp_from_thumb(
    BillboardModel *model, void *nsbmd, void *nsbtp, int unused);
extern const Vec3 data_021565ac;

MapObject *CreateMapObjectFromModel_2_from_thumb(MapObjectOwner *owner,
                                                   void *modelName)
{
    MapObject *object;
    void *fileBuffer;

    object = (MapObject *)Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0x2c);
    fileBuffer = FormatFindMapObjFileBuffer_from_thumb(modelName);

    if (owner != 0) {
        owner->loaded = 2;
    }

    object->model = (BillboardModel *)Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0x2c);
    BillboardModel_CreateFromNsbmdNsbtp_from_thumb(object->model, fileBuffer,
                                                    0, 0);
    object->model->flags_10 &= 0xc0ffffff;
    object->model->flags_10 |= 0x04000000;
    object->model->flags_14 &= ~0xf;
    object->model->flags_14 |= 2;
    object->position = data_021565ac;
    return object;
}
