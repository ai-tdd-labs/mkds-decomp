// PURPOSE: Allocates and clears a small driver sub-object.
// The argument receives the newly allocated object pointer.
// The object is probably a small driver-owned state record.

typedef unsigned int u32;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *ctx);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);

void AllocateNewDriverSub208(void **out) {
    *out = Mem_AllocateHeap(ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0x1c);
    *(u32 *)*out = 0; // Clear the first state field.
}
