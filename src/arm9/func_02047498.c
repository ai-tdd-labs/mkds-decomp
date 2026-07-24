// PURPOSE: Queues archive data for loading through a selected runtime slot.
// The first argument supplies the archive source.
// The second argument selects the runtime slot and its loading options.
// The slot is marked as pending after the request is queued.

typedef unsigned char u8;

typedef struct ArcHeapRef {
    void *heap;
    void *output;
    unsigned int options : 29;
    signed int usesSharedSource : 1;
    unsigned int unknown : 1;
    unsigned int pending : 1;
} ArcHeapRef;

typedef struct ArcRuntimeState {
    u8 padding_000[0x9b0];
    ArcHeapRef heapRefs[16];
} ArcRuntimeState;

extern ArcRuntimeState *data_021759c8;
extern void func_0204f4d0(void *source, void *heap, void **output,
                          unsigned int options, int useSharedSource);

void func_02047498(void *source, int index)
{
    ArcHeapRef *heapRef = &data_021759c8->heapRefs[index];

    func_0204f4d0(source, heapRef->heap, &heapRef->output,
                  heapRef->options, heapRef->usesSharedSource);
    heapRef->pending = 1;
}
