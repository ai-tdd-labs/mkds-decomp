// PURPOSE: Allocates aligned memory from a supported heap.
// The heap, requested byte count, and alignment are passed to its allocator.
// Expandable heaps allocate directly; frame heaps probably require interrupts disabled.
// An unsupported heap signature returns a null pointer.

typedef unsigned int u32;

extern void *Mem_Exp_Allocate(void *heap, unsigned int size, int alignment);
extern void *Mem_Frame_Allocate(void *heap, unsigned int size, int alignment);
extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 irqState);

void *Mem_AllocateHeapAligned(void *heap, unsigned int size, int alignment)
{
    void *allocatedBlock = 0;

    switch (*(u32 *)heap) {
    case 0x45585048: /* Expandable-heap signature. */
        allocatedBlock = Mem_Exp_Allocate(heap, size, alignment);
        break;
    case 0x46524d48: { /* Frame-heap signature. */
        u32 irqState = Os_DisableIrq();

        allocatedBlock = Mem_Frame_Allocate(heap, size, alignment);
        Os_RestoreIrq(irqState);
        break;
    }
    }

    return allocatedBlock;
}
