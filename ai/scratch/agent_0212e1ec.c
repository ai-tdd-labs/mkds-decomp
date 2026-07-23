// PURPOSE: Prepares data for a sound wave archive.
// The caller supplies file metadata, an identifier, and a dynamic-load flag.
// It uses existing raw data when available, otherwise probably loads the full file.
// Dynamic data is recorded in the file metadata after a successful load.

typedef unsigned int u32;

extern void *Sound_MaybeGetRawFilePointer(void *fileFat);
extern void *Sound_GetActiveSdat(void);
extern void *Sound_AllocateReadEntireFile(void *fileFat, void (*destructor)(void),
                                           void *sdat, void *owner, u32 fileId);
extern void Sound_SetFileFatDynamicOffsetField(void *fileFat, void *offset);
extern void AnotherSoundDtorFn(void);

void *Sound_PrepareSwarData(void *fileFat, u32 fileId, int dynamic)
{
    void *data;
    void *sdat;

    data = Sound_MaybeGetRawFilePointer(fileFat);
    if (data == 0) {
        if (dynamic != 0) {
            sdat = Sound_GetActiveSdat();
        } else {
            sdat = 0;
        }
        data = Sound_AllocateReadEntireFile(fileFat, AnotherSoundDtorFn, sdat,
                                            fileFat, fileId);
        if (dynamic != 0 && data != 0) {
            Sound_SetFileFatDynamicOffsetField(fileFat, data);
        }
    }

    return data;
}
