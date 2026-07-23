typedef unsigned int u32;

typedef struct ConfigTable209f6d8 {
    u32 pad_00[0x6b];
    void *f1ac;
} ConfigTable209f6d8;

extern void func_020d2398(void *entry);
extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *ctx);
extern void *Mem_AllocateHeap(void *heap, u32 size);
extern void StructMQRacerEntry_SomeFn_45(void *obj, u32 kind, void *arg2);
extern void func_0210bae8(void *obj);

extern ConfigTable209f6d8 data_0217ca6c;

/* PURPOSE: Initialize a racer entry's sub-object and cache a config pointer into it. */
void func_020a6c64(void *entry) {
    char *r4 = (char *)entry;

    func_020d2398(r4);

    void *ctx = GetActiveExecutionContext();
    void *heap = ExecutionContext_GetHeapHandle(ctx);
    void *obj = Mem_AllocateHeap(heap, 0x44);
    *(void **)(r4 + 0x94) = obj;

    StructMQRacerEntry_SomeFn_45(*(void **)(r4 + 0x94), 0xb, r4 + 4);
    func_0210bae8(*(void **)(r4 + 0x94));

    *(void **)(r4 + 0x70) = data_0217ca6c.f1ac;
}
