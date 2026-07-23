// PURPOSE: Returns the largest aligned allocation available in an expanded heap.
// The heap and requested alignment are supplied by the caller.
// It scans the free blocks and returns the biggest aligned region.

typedef unsigned int u32;

typedef struct ExpBlock {
    u32 unused0;
    u32 size;
    u32 unused8;
    struct ExpBlock *next;
} ExpBlock;

typedef struct ExpHeap {
    unsigned char unused[0x24];
    ExpBlock *freeBlocks;
} ExpHeap;

extern int abs(int value);

u32 Mem_Exp_GetAllocatableSize(ExpHeap *heap, int alignment)
{
    u32 largestSize;
    u32 largestOffset;
    ExpBlock *block;

    alignment = abs(alignment);
    block = heap->freeBlocks;
    largestSize = 0;
    largestOffset = (u32)-1;

    if (block != 0) {
        do {
            u32 blockStart = (u32)block + 0x10;
            u32 alignedStart = (((u32)alignment - 1) + blockStart) &
                               ~((u32)alignment - 1);
            u32 blockEnd = block->size + blockStart;

            if (alignedStart < blockEnd) {
                u32 size = blockEnd - alignedStart;
                u32 offset = alignedStart - blockStart;

                if (largestSize < size ||
                    (largestSize == size && largestOffset > offset)) {
                    largestSize = size;
                    largestOffset = offset;
                }
            }

            block = block->next;
        } while (block != 0);
    }

    return largestSize;
}
