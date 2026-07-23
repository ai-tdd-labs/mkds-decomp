typedef unsigned int u32;
typedef struct Obj2c { u32 w[11]; } Obj2c;
extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *ctx);
extern void *Mem_AllocateHeap(void *heap, u32 size);
extern void func_020d49d8(void *arg);
extern Obj2c *data_0217c62c;
extern const Obj2c data_0215a100;
void *Maybe_CreateObj_15a100(void) {
    void *ctx = GetActiveExecutionContext();
    void *heap = ExecutionContext_GetHeapHandle(ctx);
    Obj2c *obj = (Obj2c *)Mem_AllocateHeap(heap, 0x2c);
    data_0217c62c = obj;
    *obj = data_0215a100;
    func_020d49d8(&data_0217c62c);
    return data_0217c62c;
}
