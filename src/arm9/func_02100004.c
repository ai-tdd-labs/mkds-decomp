// PURPOSE: Creates and clears a small heap object.
// Allocates 0x40 bytes from the active execution context's heap.
// The returned object's 16 words are initialized to zero.

typedef unsigned int u32;

typedef struct Obj40 {
    u32 words[0x10];
} Obj40;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);

void *func_02100004(void) {
    void *context = GetActiveExecutionContext();
    void *heap = ExecutionContext_GetHeapHandle(context);
    Obj40 *object = (Obj40 *)Mem_AllocateHeap(heap, 0x40);
    Obj40 value = { 0 };

    *object = value;
    return object;
}
