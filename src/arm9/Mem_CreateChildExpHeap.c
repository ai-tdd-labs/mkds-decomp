// PURPOSE: Creates an expandable child heap from all available parent heap space.
// The parent heap type selects how its available size and storage are obtained.
// Unsupported heap types pass a null storage pointer and zero size onward.
// The allocated storage becomes a forward-growing expandable heap.

typedef unsigned int u32;

extern u32 Mem_Exp_GetAllocatableSize(void *heap, int alignment);
extern u32 Mem_Frame_GetAllocatableSize(void *heap, int alignment);
extern void *Mem_Exp_Allocate(void *heap, unsigned int size, int alignment);
extern void *Mem_Frame_Allocate(void *heap, unsigned int size, int alignment);
extern void *Mem_Exp_Create(void *start, u32 size, int direction);

void *Mem_CreateChildExpHeap(void *heap)
{
    u32 allocatableSize = 0;

    switch (*(u32 *)heap) {
    case 0x45585048: /* Expandable-heap signature. */
        allocatableSize = Mem_Exp_GetAllocatableSize(heap, 4);
        break;
    case 0x46524d48: /* Frame-heap signature. */
        allocatableSize = Mem_Frame_GetAllocatableSize(heap, 4);
        break;
    }

    {
        void *childStorage = 0;

        switch (*(u32 *)heap) {
        case 0x45585048:
            childStorage = Mem_Exp_Allocate(heap, allocatableSize, 4);
            break;
        case 0x46524d48:
            childStorage = Mem_Frame_Allocate(heap, allocatableSize, 4);
            break;
        }

        return Mem_Exp_Create(childStorage, allocatableSize, 1);
    }
}
