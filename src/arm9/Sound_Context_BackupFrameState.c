// PURPOSE: Saves the sound context's current frame memory state.
// The context supplies a heap pointer and a frame-state slot.
// It probably resets sound state before deciding whether to keep the backup.
// A failed backup or reset path restores the heap and returns an error.

typedef struct {
    void *heap;
    unsigned char pad04[0x8];
    unsigned short frameState;
} SoundContext;

extern int Mem_CreateFrameHeapState(void *heap, unsigned short frameState);
extern void Mem_RestoreFrameHeapState(void *heap, int state);
extern int Sound_Context_MaybeReset(SoundContext *context);

int Sound_Context_BackupFrameState(SoundContext *context)
{
    if (Mem_CreateFrameHeapState(context->heap, context->frameState) == 0) {
        return -1;
    }

    if (Sound_Context_MaybeReset(context) != 0) {
        return context->frameState - 1;
    }

    Mem_RestoreFrameHeapState(context->heap, 0);
    return -1;
}
