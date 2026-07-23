// PURPOSE: Creates a private copy of this object's pointer list when needed.
// The object holds a pointer list, a halfword element count, and an ownership flag.
// When the flag is clear, it reuses the original list instead.
// The exact object type is probably part of an internal resource loader.

typedef struct PointerListOwner {
    void **source;
    unsigned short count;
    unsigned char padding[0x16];
    void *copyRequired;
    void *reserved;
    void **list;
} PointerListOwner;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);

void func_020d4990(PointerListOwner *owner)
{
    int i;

    if (owner->copyRequired != 0) {
        owner->list = Mem_AllocateHeap(
            ExecutionContext_GetHeapHandle(GetActiveExecutionContext()),
            (unsigned int)owner->count << 2);

        for (i = 0; i < owner->count; i++) {
            owner->list[i] = owner->source[i];
        }
    } else {
        owner->list = owner->source;
    }
}
