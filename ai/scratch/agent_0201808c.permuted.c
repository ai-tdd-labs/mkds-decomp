// PURPOSE: Allocates an aligned block from a frame heap.
// Zero-size requests reserve one byte before word alignment.
// Nonnegative alignment takes space from the head; negative alignment takes it from the tail.

extern void *Mem_Frame_AllocFromHead(void *heap, unsigned int size, int alignment);
extern void *Mem_Frame_AllocFromTail(void *heap, unsigned int size, int alignment);

void *Mem_Frame_Allocate(void *heap, unsigned int size, int alignment)
{
    if (size == 0) {
        size = 1;
    }

    heap = (char *)heap + 0x24;
    size = (size + 3) & ~3u;

    if (alignment >= 0) {
        return Mem_Frame_AllocFromHead(heap, size, alignment);
    }

    return Mem_Frame_AllocFromTail(heap, size, -alignment);
}
