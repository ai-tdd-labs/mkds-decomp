typedef unsigned int u32;

typedef struct Obj28 {
    u32 w[10];
} Obj28;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *ctx);
extern void *Mem_AllocateHeap(void *heap, u32 size);
extern void func_020e6f50(void *arg);

extern Obj28 *data_0217b7f4;
extern const Obj28 data_02158ff0;

void *Maybe_CreateObj_158ff0(void) {
    void *ctx = GetActiveExecutionContext();
    void *heap = ExecutionContext_GetHeapHandle(ctx);
    Obj28 *obj = (Obj28 *)Mem_AllocateHeap(heap, 0x28);
    data_0217b7f4 = obj;
    *obj = data_02158ff0;
    func_020e6f50(&data_0217b7f4);
    return data_0217b7f4;
}
