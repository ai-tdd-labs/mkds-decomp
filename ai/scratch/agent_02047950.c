// PURPOSE: Finds a file buffer for the current scene.
// Chooses the existing buffer in scene 3.
// Other scenes load and allocate the requested file buffer.

extern int GetCurrentSceneId(void);
extern void *FindFileBuffer_KME_KM1_KM2_KSB_from_thumb(const char *path);
extern void *AllocateFindFileBuffer_KME_KM1_KM2_KSB_from_thumb(const char *path);

void *FindFileBufferGeneric_KME_KM1_KM2_KSB_from_thumb(const char *path)
{
    if (GetCurrentSceneId() == 3) {
        return FindFileBuffer_KME_KM1_KM2_KSB_from_thumb(path);
    }
    return AllocateFindFileBuffer_KME_KM1_KM2_KSB_from_thumb(path);
}
