// PURPOSE: Creates a map object with its supplied setup values.
// The arguments are saved in the newly allocated object.
// The object is probably used later by the map system.

typedef struct MapObject {
    int reserved0;
    int reserved4;
    void *arg0;
    int arg2;
    void *arg1;
    int state;
    int type;
} MapObject;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);

void *CreateAllocateMapObject_from_thumb(void *arg0, void *arg1, int arg2)
{
    MapObject *object;

    object = (MapObject *)Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0x2c);
    object->type = 2;
    object->arg0 = arg0;
    object->arg2 = arg2;
    object->arg1 = arg1;
    object->state = 0;
    return object;
}
