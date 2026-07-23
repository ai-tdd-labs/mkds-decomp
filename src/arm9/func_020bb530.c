// PURPOSE: Creates the shared work record with its default values.
// The record is allocated from the active execution context's heap.
// Its fields receive the default values used by this probably scene-specific system.

typedef struct WorkRecordB3CC {
    void *field_00;
    void *field_04;
    unsigned int field_08;
    unsigned int field_0C;
    void *field_10;
    void *field_14;
    void *field_18;
    unsigned int field_1C;
    unsigned int field_20;
    int field_24;
    unsigned int field_28;
} WorkRecordB3CC;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern WorkRecordB3CC *data_0217b3cc;

void func_020bb530(void)
{
    data_0217b3cc = (WorkRecordB3CC *)Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0x2c);
    data_0217b3cc->field_00 = 0;
    data_0217b3cc->field_04 = 0;
    data_0217b3cc->field_08 = 0x13;
    data_0217b3cc->field_0C = 0x13;
    data_0217b3cc->field_10 = 0;
    data_0217b3cc->field_14 = 0;
    data_0217b3cc->field_18 = 0;
    data_0217b3cc->field_1C = 0x1000;
    data_0217b3cc->field_20 = 0x1000;
    data_0217b3cc->field_24 = -0x666;
    data_0217b3cc->field_28 = 0x800;
}
