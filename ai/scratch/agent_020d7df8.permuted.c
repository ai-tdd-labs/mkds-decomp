// PURPOSE: Allocates and initializes one entry for every course path item.

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct CoursePathState {
    u8 _00[0x0c];
    u16 pointCount;
} CoursePathState;

typedef struct CoursePointEntry {
    int value;
    u8 _04[8];
} CoursePointEntry;

extern CoursePathState *data_02175620;
extern CoursePointEntry *data_0217b670;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);

void func_020d7df8(void)
{
    u16 pointCount = data_02175620->pointCount;
    int index;
    int offset;
    int value;

    if (pointCount != 0) {
        data_0217b670 = Mem_AllocateHeap(
            ExecutionContext_GetHeapHandle(GetActiveExecutionContext()),
            pointCount * 12);
    }

    index = 0;
    offset = 0;
    value = index;
    if (index < pointCount) {
        do {
            *(int *)((u8 *)data_0217b670 + offset) = value;
            offset += 12;
            index++;
        } while (index < pointCount);
    }
}
