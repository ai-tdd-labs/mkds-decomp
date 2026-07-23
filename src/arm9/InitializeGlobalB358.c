// PURPOSE: Creates and clears the shared global work record.
// The record uses memory from the active execution context's heap.
// Its three pointer-sized fields are initially empty.
// The exact role of this record is probably scene-specific.

typedef struct GlobalB358 {
    void *field_00;
    void *field_04;
    void *field_08;
} GlobalB358;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern GlobalB358 *data_0217b358;

void InitializeGlobalB358(void)
{
    data_0217b358 = (GlobalB358 *)Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0xc);
    data_0217b358->field_00 = 0;
    data_0217b358->field_04 = 0;
    data_0217b358->field_08 = 0;
}
