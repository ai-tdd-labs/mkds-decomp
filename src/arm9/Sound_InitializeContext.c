// PURPOSE: Creates and prepares a sound context in a memory range.
// The range is aligned before a frame heap is created after the context header.
// The context is returned only when its sound allocator setup succeeds.

typedef unsigned int u32;

typedef struct SoundContext {
    void *heap;
    char allocationList[0x0c];
} SoundContext;

extern void *Mem_Frame_Create(void *start, u32 size, int direction);
extern void Mem_Frame_Finalize(void *heap);
extern int Sound_Context_SetHeap(SoundContext *context, void *heap);

SoundContext *Sound_InitializeContext(void *start, u32 size)
{
    u32 end = (u32)start + size;
    SoundContext *context = (SoundContext *)(((u32)start + 3) & ~3);
    void *heap;

    if ((u32)context > end) {
        return 0;
    }

    size = end - (u32)context;
    if (size < 0x10) {
        return 0;
    }

    heap = Mem_Frame_Create((void *)((u32)context + 0x10), size - 0x10, 0);
    if (heap == 0) {
        return 0;
    }

    if (Sound_Context_SetHeap(context, heap) != 0) {
        return context;
    }

    Mem_Frame_Finalize(heap);
    return 0;
}
