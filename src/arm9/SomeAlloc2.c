// PURPOSE: Allocates and saves a small shared memory block.
// It obtains the current execution context and its heap handle.
// The four-byte allocation is probably used by a nearby game system.

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void *data_0217b4a8;

void SomeAlloc2(void)
{
    data_0217b4a8 = Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 4);
}
