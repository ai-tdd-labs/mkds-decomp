/* PURPOSE: Creates a child frame heap at the start of a parent heap.
 * The parent heap supplies a block of the requested size with four-byte alignment.
 * Expandable and frame heaps use their matching allocation routines.
 * The allocated block becomes a frame heap that grows from its head.
 */

typedef unsigned int u32;

extern void *Mem_Exp_Allocate(void *heap, unsigned int size, int alignment);
extern void *Mem_Frame_Allocate(void *heap, unsigned int size, int alignment);
extern void *Mem_Frame_Create(void *start, u32 size, int direction);

void *Mem_CreateChildFrameHeapFromHead(void *heap, unsigned int size)
{
    void *childStorage = 0;

    switch (*(u32 *)heap) {
    case 0x45585048: /* Expandable-heap signature. */
        childStorage = Mem_Exp_Allocate(heap, size, 4);
        break;
    case 0x46524d48: /* Frame-heap signature. */
        childStorage = Mem_Frame_Allocate(heap, size, 4);
        break;
    }

    return Mem_Frame_Create(childStorage, size, 1);
}
