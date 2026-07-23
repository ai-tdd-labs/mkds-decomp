// PURPOSE: Adds an animation file to a map object.
// The object supplies the animation settings and receives the allocated state.
// The file name is probably resolved from the caller's map-object resource.

typedef struct StructMapObject {
    char _pad0[0x10];
    void *field_10;
    char _pad14[4];
    void *field_18;
    char _pad1c[4];
    void *field_20;
} StructMapObject;

extern void *FormatFindMapObjFileBuffer_from_thumb(void *name);
extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void SomeAnimationLoadWrapper_from_thumb(int type, void *field_10,
                                                  void *state, void *field_18,
                                                  void *file_buffer);

void StructMapObject_AddAnimationNsbtp_from_thumb(StructMapObject *map_object,
                                                   void *name)
{
    void *file_buffer;

    file_buffer = FormatFindMapObjFileBuffer_from_thumb(name);
    map_object->field_20 = Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0x38);
    SomeAnimationLoadWrapper_from_thumb(2, map_object->field_10,
                                         map_object->field_20,
                                         map_object->field_18, file_buffer);
}
