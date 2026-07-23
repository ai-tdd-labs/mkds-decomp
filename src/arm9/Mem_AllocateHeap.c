/* PURPOSE: Allocates memory from a supported heap.
 * The heap and requested byte count are passed to the matching allocator.
 * Expandable and frame heaps use four-byte alignment.
 * An unsupported heap signature returns a null pointer.
 */

typedef unsigned int u32;

extern void *Mem_Exp_Allocate(void *heap, unsigned int size, int alignment);
extern void *Mem_Frame_Allocate(void *heap, unsigned int size, int alignment);

void *Mem_AllocateHeap(void *heap, unsigned int size)
{
    void *allocatedBlock = 0;

    switch (*(u32 *)heap) {
    case 0x45585048: /* Expandable-heap signature. */
        allocatedBlock = Mem_Exp_Allocate(heap, size, 4);
        break;
    case 0x46524d48: /* Frame-heap signature. */
        allocatedBlock = Mem_Frame_Allocate(heap, size, 4);
        break;
    }

    return allocatedBlock;
}
