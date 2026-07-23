// PURPOSE: Allocates the global RE memory block.
// Uses the supplied heap to create a probably shared ten-byte allocation.
// Stores the allocation in the global pointer and returns the requested size.

extern void *data_0217aa18;
extern void *Mem_AllocateHeap(void *heap, unsigned int size);

int InitializeGlobalRE(void *heap)
{
    data_0217aa18 = Mem_AllocateHeap(heap, 10);
    return 10;
}
