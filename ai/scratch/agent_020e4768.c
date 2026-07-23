/*
PURPOSE: Creates an object from a template with a fixed initial value.
This function allocates a 0x40-byte object from the active heap.
It copies the template data, sets the word at offset 0x38, and returns the object.
The exact meaning of the field at offset 0x38 is unknown.
*/

typedef unsigned int u32;

typedef struct Obj40 {
    u32 words[0x10];
} Obj40;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, u32 size);

extern const Obj40 data_02158f70;

void *func_020e4768(void) {
    void *context = GetActiveExecutionContext();
    void *heap = ExecutionContext_GetHeapHandle(context);
    Obj40 *object = (Obj40 *)Mem_AllocateHeap(heap, 0x40);

    *object = data_02158f70;
    object->words[14] = 0x2bc000;
    return object;
}
