// PURPOSE: Creates the shared lap progress record.
// The record is allocated from the active execution context's heap.
// It starts empty, records the current lap minus one, and enables its final flag.
// Its exact scene-specific role is probably unknown.

typedef struct LapProgressRecord {
    void *field_00;
    void *field_04;
    unsigned int field_08;
    void *field_0C;
    unsigned int field_10;
} LapProgressRecord;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern int GetCurrentLapCount(void);
extern LapProgressRecord *data_0217b3d4;

void func_020bcb74(void)
{
    data_0217b3d4 = (LapProgressRecord *)Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0x14);
    data_0217b3d4->field_00 = 0;
    data_0217b3d4->field_04 = 0;
    data_0217b3d4->field_08 = (unsigned short)(GetCurrentLapCount() - 1);
    data_0217b3d4->field_0C = 0;
    data_0217b3d4->field_10 = 1;
}
