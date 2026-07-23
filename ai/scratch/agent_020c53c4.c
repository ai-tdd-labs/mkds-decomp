// PURPOSE: Creates and clears the shared global work record.
// The record is allocated from the active execution context's heap.
// Its five pointer-sized fields start empty.
// Its exact scene-specific role is probably unknown.

typedef struct GlobalB3EC {
    void *field_00;
    void *field_04;
    void *field_08;
    void *field_0C;
    void *field_10;
} GlobalB3EC;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern GlobalB3EC *data_0217b3ec;

void CreateGlobalB3EC(void)
{
    data_0217b3ec = (GlobalB3EC *)Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0x14);
    data_0217b3ec->field_00 = 0;
    data_0217b3ec->field_04 = 0;
    data_0217b3ec->field_08 = 0;
    data_0217b3ec->field_0C = 0;
    data_0217b3ec->field_10 = 0;
}
