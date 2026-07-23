// PURPOSE: Allocates a block from the end of a frame heap.
// The heap tracks its lower allocation limit and current tail pointer.
// The requested size is rounded down from the tail to the requested alignment.
// The heap probably clears allocated blocks when its low flag bit is set.

typedef unsigned int u32;
typedef unsigned short u16;

extern void MIi_CpuClear32(u32 value, void *destination, u32 size);

typedef struct {
    void *head;
    void *tail;
} FrameHeap;

void *Mem_Frame_AllocFromTail(FrameHeap *heap, u32 size, u32 alignment)
{
    void *allocated;
    u32 allocatedSize;

    allocated = (void *)(((u32)heap->tail - size) & ~(alignment - 1));
    if (allocated < heap->head) {
        return 0;
    }

    allocatedSize = (u32)heap->tail - (u32)allocated;
    {
        u32 flags = ((u32 *)heap)[-1];
        if ((u16)(flags & 0xff) & 1) {
        volatile u32 clearValue = 0;
        MIi_CpuClear32(clearValue, allocated, allocatedSize);
        }
    }

    heap->tail = allocated;
    return allocated;
}
