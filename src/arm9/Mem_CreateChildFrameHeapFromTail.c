// PURPOSE: Creates a child frame heap that grows from the end of a parent heap.
// The parent heap supplies storage for the requested byte count.
// Expandable heaps allocate directly; frame heaps allocate with interrupts disabled.
// The storage is then initialized as a tail-growing frame heap.

typedef unsigned int u32;

extern void *Mem_Exp_Allocate(void *heap, unsigned int size, int alignment);
extern void *Mem_Frame_Allocate(void *heap, unsigned int size, int alignment);
extern void *Mem_Frame_Create(void *start, u32 size, int direction);
extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 irqState);

void *Mem_CreateChildFrameHeapFromTail(void *heap, unsigned int size)
{
    void *childStorage = 0;

    switch (*(u32 *)heap) {
    case 0x45585048:
        childStorage = Mem_Exp_Allocate(heap, size, -4);
        break;
    case 0x46524d48: {
        u32 irqState = Os_DisableIrq();

        childStorage = Mem_Frame_Allocate(heap, size, -4);
        Os_RestoreIrq(irqState);
        break;
    }
    }

    return Mem_Frame_Create(childStorage, size, 1);
}
