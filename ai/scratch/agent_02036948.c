// PURPOSE: Creates a frame heap from all unused space in a parent heap.
// The parent heap type determines how much space is available and how it is allocated.
// Unsupported heap types provide no storage and create an empty child heap.

typedef unsigned int u32;

extern u32 Mem_Exp_GetAllocatableSize(void *heap, int alignment);
extern u32 Mem_Frame_GetAllocatableSize(void *heap, int alignment);
extern void *Mem_Exp_Allocate(void *heap, unsigned int size, int alignment);
extern void *Mem_Frame_Allocate(void *heap, unsigned int size, int alignment);
extern void *Mem_Frame_Create(void *start, u32 size, int direction);

void *Mem_CreateOrphanChildHeap(void *heap)
{
    u32 allocatableSize = 0;

    switch (*(u32 *)heap) {
    case 0x45585048:
        allocatableSize = Mem_Exp_GetAllocatableSize(heap, 4);
        break;
    case 0x46524d48:
        allocatableSize = Mem_Frame_GetAllocatableSize(heap, 4);
        break;
    }

    switch (*(u32 *)heap) {
    case 0x45585048:
        heap = Mem_Exp_Allocate(heap, allocatableSize, 4);
        break;
    case 0x46524d48:
        heap = Mem_Frame_Allocate(heap, allocatableSize, 4);
        break;
    default:
        heap = 0;
        break;
    }

    return Mem_Frame_Create(heap, allocatableSize, 1);
}
