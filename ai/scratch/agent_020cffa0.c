// PURPOSE: Allocates the probably active context's 56-byte work buffer.
// The active execution context supplies the heap used for the allocation.
// The resulting pointer is stored in a shared, probably work-state slot.

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void *data_0217b490;

void SomeAlloc(void)
{
    data_0217b490 = Mem_AllocateHeap(ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0x38);
}
