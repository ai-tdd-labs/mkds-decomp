// PURPOSE: Allocates and clears the shared work record.
// It gets a 0x194-byte record from the active execution context's heap.
// Several pointer, halfword, and word tables are cleared for eight entries.
// The record's exact scene-specific role is probably unknown.

typedef struct AnotherAllocPair {
    void *field_00;
    void *field_04;
} AnotherAllocPair;

typedef struct AnotherAllocRecord {
    void *field_000[8];
    void *field_020[8];
    AnotherAllocPair field_060[8];
    unsigned char padding_0a0[0x60];
    unsigned short field_100[8];
    unsigned char padding_110[0x20];
    unsigned int field_130[8];
    unsigned char padding_150[0x40];
} AnotherAllocRecord;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void func_020c0ba8(void *record_tail, unsigned int count);
extern AnotherAllocRecord *data_0217b428;

void AnotherAlloc_1(void)
{
    unsigned int i;

    data_0217b428 = (AnotherAllocRecord *)Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0x194);
    func_020c0ba8((char *)data_0217b428 + 0x190, 0x18);

    for (i = 0; i < 8; i++) {
        data_0217b428->field_000[i] = 0;
        data_0217b428->field_020[i] = 0;
        data_0217b428->field_060[i].field_00 = 0;
        data_0217b428->field_060[i].field_04 = 0;
        data_0217b428->field_100[i] = 0;
        data_0217b428->field_130[i] = 0;
    }

    return 1;
}
