// PURPOSE: Allocates and clears the shared work record.
// The record is allocated from the active execution context's heap.
// Its four fields are initially empty; its exact scene role is probably unknown.

typedef struct AnotherAllocRecord {
    void *field_00;
    void *field_04;
    void *field_08;
    void *field_0c;
} AnotherAllocRecord;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern AnotherAllocRecord *data_0217b35c;

void AnotherAlloc(void)
{
    data_0217b35c = (AnotherAllocRecord *)Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0x10);
    data_0217b35c->field_00 = 0;
    data_0217b35c->field_04 = 0;
    data_0217b35c->field_08 = 0;
    data_0217b35c->field_0c = 0;
}
