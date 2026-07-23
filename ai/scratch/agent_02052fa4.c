// PURPOSE: Allocates or frees memory while interrupts are disabled.
typedef unsigned int u32;

typedef struct UnkStruct_0217aa00 {
    char _00[0x1d04];
    void *heap;
} UnkStruct_0217aa00;

extern UnkStruct_0217aa00 *data_0217aa00;
extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 irqState);
extern void Mem_FreeHeap(void *heap, void *block);
extern void *Mem_AllocateHeapAligned(void *heap, unsigned int size, int alignment);

void *func_02052fa4(int unused, unsigned int size, void *block)
{
    u32 irqState;
    void *result = 0;

    irqState = Os_DisableIrq();
    if (block != 0) {
        Mem_FreeHeap(data_0217aa00->heap, block);
    } else {
        result = Mem_AllocateHeapAligned(data_0217aa00->heap, size, -0x20);
    }
    Os_RestoreIrq(irqState);

    return result;
}
