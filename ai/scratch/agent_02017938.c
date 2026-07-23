/*
PURPOSE: Allocates an aligned block from an expandable heap.
The heap is passed in heap, and size is rounded up to four bytes after a
zero-byte request is promoted to one byte. A nonnegative alignment allocates
from the heap head; a negative alignment selects the tail using its magnitude.
*/

extern void *Mem_Exp_AllocFromHead(void *heap, unsigned int size, int alignment);
extern void *Mem_Exp_AllocFromTail(void *heap, unsigned int size, int alignment);

void *Mem_Exp_Allocate(void *heap, unsigned int size, int alignment)
{
    if (size == 0) {
        size = 1;
    }

    size = (size + 3) & ~3u;

    if (alignment >= 0) {
        return Mem_Exp_AllocFromHead(heap, size, alignment);
    } else {
        return Mem_Exp_AllocFromTail(heap, size, -alignment);
    }
}
