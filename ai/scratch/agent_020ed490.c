/*
PURPOSE: Creates a 3D item model from an item resource.
The argument identifies the item model file to load.  The function allocates
a model wrapper, initializes it from the file buffer, applies rendering flags,
and returns the completed wrapper.
*/

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void *FindItemFileBuffer_from_thumb(char *resource);
extern void Model_CreateFromNsbmd(void *model, void *fileBuffer);
extern void Model_SetPolygonIdLightFlagsEmi(void *model, int polygonId, int lightFlags, int emission);

void *func_020ed490(char *resource)
{
    void *model;

    model = Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0x6c);
    Model_CreateFromNsbmd(model, FindItemFileBuffer_from_thumb(resource));
    Model_SetPolygonIdLightFlagsEmi(model, 4, 2, 0x294a);

    return model;
}
