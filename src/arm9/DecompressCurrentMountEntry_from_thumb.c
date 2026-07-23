// PURPOSE: Decompresses the archive data for the current mount entry.
// The current entry probably owns a compressed archive and its output buffer.
// It allocates the output with an alignment selected by the entry flag, decompresses it,
// cleans the data cache, and returns the active heap's remaining free size.

typedef unsigned int u32;

typedef struct CurrentMountEntry {
    char pad_00[0x80];
    void *compressedData;
    void *decompressedData;
    char pad_88[8];
    int useNegativeAlignment;
} CurrentMountEntry;

typedef struct ArcRuntimeState {
    char pad_000[0x8c8];
    CurrentMountEntry currentMountEntry;
} ArcRuntimeState;

extern ArcRuntimeState *data_021759c8;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeapAligned(void *heap, u32 size, int alignment);
extern void DecompressLzss(const void *source, void *destination);
extern void DC_SomeClean(void *address, u32 size);
extern u32 Mem_GetExpHeapTotalFreeSize(void *heap);

u32 DecompressCurrentMountEntry_from_thumb(void)
{
    CurrentMountEntry *entry = &data_021759c8->currentMountEntry;
    u32 size = *(u32 *)entry->compressedData >> 8;

    if (entry->useNegativeAlignment != 0) {
        entry->decompressedData = Mem_AllocateHeapAligned(
            ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), size, -32);
    } else {
        entry->decompressedData = Mem_AllocateHeapAligned(
            ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), size, 32);
    }

    DecompressLzss(entry->compressedData, entry->decompressedData);
    DC_SomeClean(entry->decompressedData, size);
    return Mem_GetExpHeapTotalFreeSize(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()));
}
