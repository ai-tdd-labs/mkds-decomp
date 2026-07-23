// PURPOSE: Loads a sound archive and reports whether loading failed.
// Takes an archive ID and the heap used for the archive data.
// Requests the standard load flags and preparation option.
// The output pointer is probably unused by this wrapper.

typedef unsigned int u32;

extern int Sound_GetSarcPointer(int archiveId, u32 flags, void *heap,
                                int preparationOption, void **archiveDataOut);

int Sound_LoadSarc(int archiveId, void *heap) {
    return Sound_GetSarcPointer(archiveId, 0xff, heap, 1, (void **)0) == 0;
}
