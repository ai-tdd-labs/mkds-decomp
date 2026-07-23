// PURPOSE: Allocates a shared buffer and eight small memory blocks.
// The heap argument supplies all allocations.
// The global context probably owns the resulting pointers.

typedef unsigned int u32;

typedef struct AllocateSomeZEStuffWork {
    unsigned char _0000[0x1624];
    void *buffer;
    unsigned char _1628[4];
    void *blocks[8];
} AllocateSomeZEStuffWork;

extern AllocateSomeZEStuffWork *data_0217aa00;
extern void *Mem_AllocateHeapAligned(void *heap, u32 size, u32 alignment);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);

void AllocateSomeZEStuff_from_thumb(void *heap)
{
    int i;

    data_0217aa00->buffer = Mem_AllocateHeapAligned(heap, 0x16C, 0x20);

    for (i = 0; i < 8; i++) {
        data_0217aa00->blocks[i] = Mem_AllocateHeap(heap, 0x12);
    }
}
