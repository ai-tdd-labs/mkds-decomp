// PURPOSE: Allocates and initializes this object's item storage.
// The object supplies a halfword count used to size the allocation.
// It probably starts a three-state item-processing operation.

typedef struct ItemStorage {
    void *items;
    unsigned short count;
    unsigned char padding[0x12];
    int state;
    int value;
    int mode;
} ItemStorage;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);

void func_020e6f9c(ItemStorage *storage)
{
    storage->items = Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()),
        (unsigned int)storage->count << 2);
    storage->count = 0;
    storage->state = 3;
    storage->value = 0;
    storage->mode = 3;
}
