// PURPOSE: Creates a counted heap allocation record.
// The output pointer receives a small record for the requested number of items.
// The record probably owns both an item-pointer array and a fixed-size item buffer.

typedef struct CountedHeapAllocation {
    void *unused;
    void *item_buffer;
    unsigned int count;
    void *item_pointers;
    void *items;
} CountedHeapAllocation;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void *AllocateActiveHeapSizeCount_from_thumb(unsigned int count,
                                                     unsigned int item_size);

int func_020c0ba8(CountedHeapAllocation **output, unsigned int count)
{
    if (count == 0) {
        return 0;
    }

    *output = (CountedHeapAllocation *)Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0x14);
    (*output)->item_buffer = 0;
    (*output)->count = count;
    (*output)->item_pointers = Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), count << 3);
    (*output)->items = AllocateActiveHeapSizeCount_from_thumb(count, 0x14);
    return 1;
}
