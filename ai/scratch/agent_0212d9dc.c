/* PURPOSE: Attaches a heap to a sound context and resets it for use.
 * context is the sound allocation state to initialize; heap is the allocator
 * it should use. The function clears the embedded list, stores the heap, and
 * returns whether the context reset succeeded.
 */

typedef struct SoundContext {
    void *heap;          /* 0x00 */
    char allocationList[0x0c]; /* 0x04 */
} SoundContext;

extern void IntrusiveListWrapper_InitializeEmpty(void *list, int itemSize);
extern int Sound_Context_MaybeReset(SoundContext *context);

int Sound_Context_SetHeap(SoundContext *context, void *heap)
{
    IntrusiveListWrapper_InitializeEmpty(&context->allocationList, 0x0c);
    context->heap = heap;
    return Sound_Context_MaybeReset(context) != 0;
}
