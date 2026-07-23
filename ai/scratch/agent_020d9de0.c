// PURPOSE: Allocates and clears a 64-byte heap block.
// The block comes from the active execution context's heap.
// Every word in the returned block is initialized to zero.

typedef unsigned int u32;

typedef struct Obj40 {
    u32 words[0x10];
} Obj40;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);

void *func_020d9de0(void) {
    Obj40 zero;
    void *context = GetActiveExecutionContext();
    void *heap = ExecutionContext_GetHeapHandle(context);
    Obj40 *object = (Obj40 *)Mem_AllocateHeap(heap, 0x40);

    zero = (Obj40){0};
    *object = zero;
    return object;
}
