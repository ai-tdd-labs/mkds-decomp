/* PURPOSE: Allocates tracked memory for sound data.
 * The requested payload is aligned to 32 bytes and follows a 32-byte header.
 * The header records the payload size, cleanup callback, sound archive, and
 * custom callback argument, then joins the current sound-allocation list.
 */

typedef unsigned short u16;
typedef unsigned int u32;

typedef struct IntrusiveListWrapper {
    void *first;
    void *last;
    u16 count;
    u16 linkOffset;
} IntrusiveListWrapper;

typedef struct SoundContext {
    void *heap;
    IntrusiveListWrapper allocationStates;
} SoundContext;

typedef void (*SoundDisposeCallback)(void *payload, u16 payloadSize,
                                     void *soundArchive, u32 customArgument);

typedef struct SoundAllocationHeader {
    void *previous;
    void *next;
    u32 payloadSize;
    SoundDisposeCallback disposeCallback;
    void *soundArchive;
    void *customArgument;
    u32 reserved[2];
} SoundAllocationHeader;

extern void *Mem_Frame_Allocate(void *heap, unsigned int size, int alignment);
extern IntrusiveListWrapper *IntrusiveListWrapper_GetPrevItem(
    IntrusiveListWrapper *list, void *item);
extern void IntrusiveListWrapper_InsertLast(IntrusiveListWrapper *list,
                                            void *item);

void *Sound_Context_Allocate(SoundContext *context, unsigned int payloadSize,
                             SoundDisposeCallback disposeCallback,
                             void *soundArchive, void *customArgument)
{
    SoundAllocationHeader *allocation;
    IntrusiveListWrapper *activeState;

    allocation = Mem_Frame_Allocate(
        context->heap, ((payloadSize + 0x1f) & ~0x1f) + 0x20, 0x20);
    if (allocation == 0) {
        return 0;
    }

    /* New allocations belong to the most recently saved heap state. */
    activeState = IntrusiveListWrapper_GetPrevItem(
        &context->allocationStates, 0);
    allocation->payloadSize = payloadSize;
    allocation->disposeCallback = disposeCallback;
    allocation->soundArchive = soundArchive;
    allocation->customArgument = customArgument;
    IntrusiveListWrapper_InsertLast(activeState, allocation);

    return (char *)allocation + 0x20;
}
