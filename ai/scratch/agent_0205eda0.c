// PURPOSE: Allocates a small memory block and marks it as unused.
// Takes a heap pointer and probably returns the newly allocated block.
// The first byte is set to -1 when allocation succeeds.

extern void *Mem_AllocateHeap(void *heap, unsigned int size);

void *func_0205eda0(void *heap) {
    void *memory = Mem_AllocateHeap(heap, 0xB04);

    if (memory != 0) {
        *(signed char *)memory = -1;
    }
    return memory;
}
