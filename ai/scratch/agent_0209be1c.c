// PURPOSE: Adds an NSBTA animation to a map object.
// The object supplies its model, animation state, and animation target fields.
// The given filename is resolved to a map-object file buffer before loading.

extern void *FormatFindMapObjFileBuffer_from_thumb(void *name);
extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void SomeAnimationLoadWrapper_from_thumb(int type, void *model,
                                                void *animation, void *target,
                                                void *file_buffer);

typedef struct StructMapObject {
    char pad_00[0x10];
    void *model;
    char pad_14[0x4];
    void *target;
    char pad_1c[0xc];
    void *animation;
} StructMapObject;

void StructMapObject_AddAnimationNsbta_from_thumb(StructMapObject *object,
                                                  void *name)
{
    void *file_buffer;

    file_buffer = FormatFindMapObjFileBuffer_from_thumb(name);
    object->animation = Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0x38);
    SomeAnimationLoadWrapper_from_thumb(1, object->model, object->animation,
                                        object->target, file_buffer);
}
