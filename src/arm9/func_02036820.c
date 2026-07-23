// PURPOSE: Resizes a heap to fit its current frame allocation.
// The input is probably an expandable heap managed by the memory system.
// It obtains the frame size, finds the heap's top-level parent, and resizes it.

typedef unsigned int u32;

extern u32 Mem_Frame_SomeFn4(void *heap);
extern void *Mem_FindGlobalTopParentHeapHead(void *heap);
extern void Mem_ResizeExpHeap(void *heap, void *start, u32 size);

void func_02036820(void *heap)
{
    u32 size = Mem_Frame_SomeFn4(heap);

    Mem_ResizeExpHeap(Mem_FindGlobalTopParentHeapHead(heap), heap, size);
}
