// PURPOSE: Allocates the shared 12-byte work record.
// Gets the currently active execution context's heap and saves the new record.
// The exact purpose of this global work record is probably scene-specific.

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void *data_0217bc4c;

void func_020f73a4(void)
{
    data_0217bc4c = Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0xc);
}
