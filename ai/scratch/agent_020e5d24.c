// PURPOSE: Creates and initializes a shared 40-byte object.
// Allocates the object from the active execution context's heap.
// The object is probably a shared runtime configuration block.
// Returns the newly allocated object.

typedef unsigned int u32;

typedef struct Obj28 {
    u32 w[10];
} Obj28;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *ctx);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);

extern Obj28 *data_0217b828;
extern const Obj28 data_021591b4;

void *func_020e5d24(void) {
    void *ctx = GetActiveExecutionContext();
    void *heap = ExecutionContext_GetHeapHandle(ctx);
    Obj28 *obj = (Obj28 *)Mem_AllocateHeap(heap, 0x28);

    data_0217b828 = obj;
    *obj = data_021591b4; // Copy the ROM template into the new object.
    return obj;
}
