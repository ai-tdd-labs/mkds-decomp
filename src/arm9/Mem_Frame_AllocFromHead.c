// PURPOSE: Allocates memory from the start of a frame heap.
// The heap pointer addresses its moving head and fixed end pointers.
// It probably clears newly allocated memory when the preceding heap flag is set.
// Returns zero when the requested allocation does not fit.

typedef unsigned int u32;
typedef unsigned short u16;

typedef struct {
    void *head;
    void *end;
} FrameHeap;

extern void MIi_CpuClear32(u32 value, void *destination, u32 size);

void *Mem_Frame_AllocFromHead(FrameHeap *heap, u32 size, u32 alignment)
{
    void *aligned;
    void *next;
    void *head;
    void *end;
    u32 allocated_size;

    head = heap->head;
    aligned = (void *)(((alignment - 1) + (u32)head) & ~(alignment - 1));
    end = heap->end;
    next = (char *)((u32)size + (u32)aligned);
    if (next > end) {
        return 0;
    }

    allocated_size = (u32)next - (u32)head;

    if ((u16)(((u32 *)heap)[-1] & 0xff) & 1) {
        volatile u32 clear_value = 0;

        MIi_CpuClear32(clear_value, head, allocated_size);
    }

    heap->head = next;
    return aligned;
}
