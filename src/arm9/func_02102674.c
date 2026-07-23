// PURPOSE: Builds a table of fixed-point values for a probably smooth curve.
// It allocates forty-one halfword entries from the active heap.
// The last five entries are then averaged with their preceding values.

typedef unsigned short u16;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern int _s32_div_f(int dividend, int divisor);
extern u16 *data_0217c630;

void func_02102674(void)
{
    int i;

    data_0217c630 = Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0x52);

    for (i = 0; i <= 40; i++) {
        data_0217c630[i] = (u16)_s32_div_f((40 - i) << 12, 41 - i);
    }

    i -= 5;
    while (i <= 40) {
        data_0217c630[i] = (data_0217c630[i] + data_0217c630[i - 1]) >> 1;
        i++;
    }
}
