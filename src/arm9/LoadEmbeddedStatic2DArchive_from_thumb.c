/* PURPOSE: Loads the built-in 2D graphics archive into memory.
 * Argument: heap is the heap used for the archive allocation and later contents.
 * Behaviour: gets the embedded compressed archive, allocates an aligned buffer,
 * decompresses and mounts it, records the buffer, then loads its 2D contents.
 */

typedef unsigned int u32;

typedef struct Static2DArchiveRuntime {
    char pad_000[0x850];
    char mountEntry[0x68];             /* +0x850: mount state for this archive */
    u32 isLoaded;                      /* +0x8b8 */
    void *archiveData;                 /* +0x8bc */
} Static2DArchiveRuntime;

typedef struct Static2DArchiveNames {
    char pad_00[0x4c];
    char *archiveName;                 /* +0x4c: probably the mount name */
} Static2DArchiveNames;

extern Static2DArchiveRuntime *data_021759c8;
extern Static2DArchiveNames data_02164e04;

extern const u32 *GetEmbeddedStatic2DCarcArchiveData(void);
extern void *Mem_AllocateHeapAligned(void *heap, u32 size, u32 alignment);
extern void DecompressLzssAndDCClean_from_thumb(const void *source,
                                                void *destination, u32 size);
extern void MountMountEntryFrom(void *entry, char *name, void *archiveData);
extern void LoadStatic2DContents(void *heap);

void LoadEmbeddedStatic2DArchive_from_thumb(void *heap)
{
    u32 decompressedSize;
    void *archiveData;

    /* The LZ header stores the decompressed byte count above its low byte. */
    decompressedSize = *GetEmbeddedStatic2DCarcArchiveData() >> 8;
    data_021759c8->isLoaded = 0;

    archiveData = Mem_AllocateHeapAligned(heap, decompressedSize, 0x20);
    DecompressLzssAndDCClean_from_thumb(
        GetEmbeddedStatic2DCarcArchiveData(), archiveData, decompressedSize);

    MountMountEntryFrom(data_021759c8->mountEntry,
                        data_02164e04.archiveName, archiveData);
    data_021759c8->archiveData = archiveData;
    data_021759c8->isLoaded = 1;

    LoadStatic2DContents(heap);
}
