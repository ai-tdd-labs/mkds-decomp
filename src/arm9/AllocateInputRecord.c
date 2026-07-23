// PURPOSE: Allocates and stores a new input record.
// The first argument receives the allocated record pointer.
// The second argument selects the heap used for the allocation.
// The record size is probably the fixed input-record layout size.

extern void *Mem_AllocateHeap(void *heap, unsigned int size);

void AllocateInputRecord(void **record, void *heap)
{
    *record = Mem_AllocateHeap(heap, 0xdcc);
}
