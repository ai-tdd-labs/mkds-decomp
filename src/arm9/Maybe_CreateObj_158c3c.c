typedef unsigned int u32;

typedef struct Obj40 {
    u32 w[0x10];
} Obj40;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *ctx);
extern void *Mem_AllocateHeap(void *heap, u32 size);

extern const Obj40 data_02158c3c;

void *Maybe_CreateObj_158c3c(void) {
    void *ctx = GetActiveExecutionContext();
    void *heap = ExecutionContext_GetHeapHandle(ctx);
    Obj40 *obj = (Obj40 *)Mem_AllocateHeap(heap, 0x40);
    *obj = data_02158c3c;
    return obj;
}
