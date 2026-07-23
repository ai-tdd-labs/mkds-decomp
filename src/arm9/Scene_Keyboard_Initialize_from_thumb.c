// PURPOSE: Allocates and initializes the keyboard scene context.
// The argument supplies the keyboard scene's initial signed value.
// The allocated context is kept in the keyboard scene global.

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void InitializeKeyboardContext_from_thumb(void *heap, short initialValue);

extern void *data_0217d3fc;

void Scene_Keyboard_Initialize_from_thumb(short *scene)
{
    void *heap;

    heap = ExecutionContext_GetHeapHandle(GetActiveExecutionContext());
    data_0217d3fc = Mem_AllocateHeap(heap, 0x808);
    InitializeKeyboardContext_from_thumb(heap, scene[0]);
}
