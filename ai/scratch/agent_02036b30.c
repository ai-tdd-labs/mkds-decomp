/* PURPOSE: Frees a block from a compatible heap.
 * The first argument is a heap handle and the second is the block to free.
 * Expandable heaps release the block; frame heaps require no per-block work.
 */

typedef unsigned int u32;

extern void Mem_Exp_Free(void *heap, void *block);

void Mem_FreeHeap(void *heap, void *block)
{
    switch (*(u32 *)heap) {
    case 0x45585048: /* Expandable-heap signature. */
        Mem_Exp_Free(heap, block);
        break;
    case 0x46524d48: /* Frame-heap signature. */
        break;
    }
}
