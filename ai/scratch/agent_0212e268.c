// PURPOSE: Prepares sound-bank data for use.
// It returns existing raw data when possible, or probably loads the bank into the supplied heap.
// The option selects the active sound archive and records newly loaded dynamic data.

extern void *Sound_MaybeGetRawFilePointer(void *file);
extern void *Sound_GetActiveSdat(void);
extern void *Sound_AllocateReadEntireFile(void *file, void (*destructor)(void),
                                          void *sdat, void *sourceFile, void *heap);
extern void Sound_SetFileFatDynamicOffsetField(void *file, void *data);
extern void SomeSoundDtorFn(void);

void *Sound_PrepareSbnkData(void *file, void *heap, int option)
{
    void *data;

    data = Sound_MaybeGetRawFilePointer(file);
    if (data == 0) {
        data = Sound_AllocateReadEntireFile(file, SomeSoundDtorFn,
                                            option ? Sound_GetActiveSdat() : 0,
                                            file, heap);
        if (option != 0 && data != 0) {
            Sound_SetFileFatDynamicOffsetField(file, data);
        }
    }
    return data;
}
