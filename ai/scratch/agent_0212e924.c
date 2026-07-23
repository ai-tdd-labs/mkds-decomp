// PURPOSE: Loads a sound wave archive into the supplied heap.
// Takes a wave archive identifier and a heap pointer.
// Returns whether the archive pointer was obtained successfully.

extern void *Sound_GetSwarPointer(int waveArchiveId, int flags, void *heap,
                                  int load, int unused);

int Sound_LoadSwar(int waveArchiveId, void *heap)
{
    return Sound_GetSwarPointer(waveArchiveId, 0xff, heap, 1, 0) == 0;
}
