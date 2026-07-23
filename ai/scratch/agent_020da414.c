typedef unsigned int u32;

typedef struct Obj40 {
    u32 w[0x10];
} Obj40;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);

void *func_020da414(void) {
    // PURPOSE: Allocates and returns a zero-initialized 64-byte object.
    void *context = GetActiveExecutionContext();
    void *heap = ExecutionContext_GetHeapHandle(context);
    Obj40 *object = (Obj40 *)Mem_AllocateHeap(heap, 0x40);
    Obj40 zero = {0};

    *object = zero;
    return object;
}
