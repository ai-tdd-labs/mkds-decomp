// PURPOSE: Allocates the global LU data block.
// The heap argument supplies memory for the probably shared LU state.
// The allocated 0x168-byte block is stored in the global pointer.

extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void *data_0217aa1c;

void InitializeGlobalLU(void *heap)
{
    data_0217aa1c = Mem_AllocateHeap(heap, 0x168);
}
