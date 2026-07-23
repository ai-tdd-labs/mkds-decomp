typedef unsigned int u32;

typedef struct Obj40 {
    u32 w[0x10];
} Obj40;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *ctx);
extern void *Mem_AllocateHeap(void *heap, u32 size);

extern const Obj40 data_0215a680;

void *Maybe_CreateObj_15a680(void) {
    void *ctx = GetActiveExecutionContext();
    void *heap = ExecutionContext_GetHeapHandle(ctx);
    Obj40 *obj = (Obj40 *)Mem_AllocateHeap(heap, 0x40);
    *obj = data_0215a680;
    return obj;
}
