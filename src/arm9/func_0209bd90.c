// PURPOSE: Creates a map object from a loaded map file.
// The first argument probably receives a loaded-state flag when present.
// The second argument supplies the map resource name.
// The returned object owns its allocated map data and file buffer.

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

typedef struct MapObject {
    Vec3 position;
    unsigned char unknown_0c[8];
    void *mapData;
} MapObject;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void *FormatFindMapObjFileBuffer_from_thumb(void *modelName);
extern void StructAD00Sh_SomeFn_2(void *mapData, void *fileBuffer, int value);
extern const Vec3 data_021565b8;

MapObject *func_0209bd90(MapObjectOwner *owner, void *modelName)
{
    MapObject *object;
    void *fileBuffer;

    object = (MapObject *)Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0x2c);
    fileBuffer = FormatFindMapObjFileBuffer_from_thumb(modelName);

    if (owner != 0) {
        owner->loaded = 1;
    }

    object->mapData = Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0x74);
    StructAD00Sh_SomeFn_2(object->mapData, fileBuffer, 0x3f);
    object->position = data_021565b8;
    return object;
}
