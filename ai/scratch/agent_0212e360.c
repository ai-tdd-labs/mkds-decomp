// PURPOSE: Prepares sequence data for the sound system.
// Loads the requested sound sequence data if it is not already available.
// When requested, it probably associates newly loaded data with the active SDAT.

typedef unsigned int u32;

extern void *Sound_MaybeGetRawFilePointer(u32 fileId);
extern void *Sound_GetActiveSdat(void);
extern void Sound_DtorFn_SomeSarcPointer(void *rawFile, u32 offset,
                                         void *soundArchive, u32 fileId);
extern void *Sound_AllocateReadEntireFile(
    u32 fileId, void (*dtor)(void *, u32, void *, u32), void *soundArchive,
    u32 dtorFileId, void *heap);
extern void Sound_SetFileFatDynamicOffsetField(u32 fileId, void *rawFile);

void *Sound_PrepareSseqData(u32 fileId, void *heap, int useActiveSdat)
{
    void *rawFile;

    rawFile = Sound_MaybeGetRawFilePointer(fileId);
    if (rawFile == 0) {
        rawFile = Sound_AllocateReadEntireFile(
            fileId, Sound_DtorFn_SomeSarcPointer,
            useActiveSdat ? Sound_GetActiveSdat() : 0, fileId, heap);
        if (useActiveSdat && rawFile != 0) {
            Sound_SetFileFatDynamicOffsetField(fileId, rawFile);
        }
    }
    return rawFile;
}
