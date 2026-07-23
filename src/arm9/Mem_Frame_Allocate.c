// PURPOSE: Allocates an aligned block from a frame heap.
// Zero-size requests are promoted to one byte before word alignment.
// Nonnegative alignment allocates from the head; negative alignment uses the tail.

extern void *Mem_Frame_AllocFromHead(void *heap, unsigned int size, int alignment);
extern void *Mem_Frame_AllocFromTail(void *heap, unsigned int size, int alignment);

void *Mem_Frame_Allocate(void *heap, unsigned int size, int alignment)
{
    void *frameHeap = (char *)heap + 0x24;

    if (size == 0) {
        size = 1;
    }

    size = (size + 3) & ~3u;

    if (alignment >= 0) {
        return Mem_Frame_AllocFromHead(frameHeap, size, alignment);
    } else {
        return Mem_Frame_AllocFromTail(frameHeap, size, -alignment);
    }
}
