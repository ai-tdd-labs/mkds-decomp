// PURPOSE: Destroys a heap and releases it from its parent.
// The heap is finalized according to its type.
// It is probably returned to an expandable parent heap when possible.

typedef unsigned int u32;

extern void Mem_Exp_Finalize(void *heap);
extern void Mem_Frame_Finalize(void *heap);
extern void *Mem_FindGlobalTopParentHeapHead(void *heap);
extern void Mem_Exp_Free(void *heap, void *block);

void Mem_DestroyHeap(void *heap)
{
    void *parentHeap;

    switch (*(u32 *)heap) {
    case 0x45585048:
        Mem_Exp_Finalize(heap);
        break;
    case 0x46524D48:
        Mem_Frame_Finalize(heap);
        break;
    }

    parentHeap = Mem_FindGlobalTopParentHeapHead(heap);
    if (parentHeap == 0) {
        return;
    }

    switch (*(u32 *)parentHeap) {
    case 0x45585048:
        Mem_Exp_Free(parentHeap, heap);
        break;
    case 0x46524D48:
        break;
    }
}
