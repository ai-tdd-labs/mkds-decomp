// PURPOSE: Creates a map object with a model and animation.

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
extern void *FormatFindMapObjFileBuffer_from_thumb(void *name);
extern void BillboardModel_CreateFromNsbmdNsbtp_from_thumb(
    BillboardModel *model, void *nsbmd, void *nsbtp, int config);
extern const Vec3 data_021565a0;

MapObject *CreateMapObjectFromModelAndAnimation_from_thumb(
    MapObjectOwner *owner, void *modelName, void *animationName)
{
    MapObject *object;
    void *modelBuffer;
    void *animationBuffer;

    object = (MapObject *)Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0x2c);
    modelBuffer = FormatFindMapObjFileBuffer_from_thumb(modelName);
    animationBuffer = FormatFindMapObjFileBuffer_from_thumb(animationName);

    if (owner != 0) {
        owner->loaded = 2;
    }

    object->model = (BillboardModel *)Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0x2c);
    BillboardModel_CreateFromNsbmdNsbtp_from_thumb(
        object->model, modelBuffer, animationBuffer, 0);
    *(u32 *)((unsigned char *)object->model + 0x10) &= 0x8000ffff;
    asm volatile ("" ::: "memory");
    *(u32 *)((unsigned char *)object->model + 0x10) |= 0x294a0000;
    *(u32 *)((unsigned char *)object->model + 0x14) &= ~0xf;
    asm volatile ("" ::: "memory");
    *(u32 *)((unsigned char *)object->model + 0x14) |= 2;
    object->position = data_021565a0;
    return object;
}
