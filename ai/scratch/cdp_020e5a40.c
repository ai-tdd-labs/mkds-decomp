typedef unsigned int u32;
typedef struct Obj2c { u32 w[11]; } Obj2c;
extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *ctx);
extern void *Mem_AllocateHeap(void *heap, u32 size);
extern void func_020d49d8(void *arg);
extern Obj2c *data_0217b824;
extern const Obj2c data_02159114;
void *Maybe_CreateObj_159114(void) {
    void *ctx = GetActiveExecutionContext();
    void *heap = ExecutionContext_GetHeapHandle(ctx);
    Obj2c *obj = (Obj2c *)Mem_AllocateHeap(heap, 0x2c);
    data_0217b824 = obj;
    *obj = data_02159114;
    func_020d49d8(&data_0217b824);
    return data_0217b824;
}
