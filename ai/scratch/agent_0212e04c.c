// PURPOSE: Releases a sound file when its sound archive is available.
// The caller supplies the file data, its active sound archive, and file metadata.
// It temporarily switches archives and clears the metadata pointer when it owns this data.
// The exact archive relationship is probably used to safely dispose of loaded sound files.

typedef unsigned int u32;

extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 irqState);
extern void *Sound_MaybeSetActiveSdat(void *sdat);
extern void *Sound_MaybeGetRawFilePointer(void *fileFat);
extern void Sound_SetFileFatDynamicOffsetField(void *fileFat, void *offset);

void Sound_DisposeFile(void *fileData, void *sdat, void *fileFat)
{
    u32 irqState;
    void *previousSdat;

    if (sdat == 0) {
        return;
    }

    irqState = Os_DisableIrq();
    previousSdat = Sound_MaybeSetActiveSdat(sdat);

    if (fileData == Sound_MaybeGetRawFilePointer(fileFat)) {
        Sound_SetFileFatDynamicOffsetField(fileFat, 0);
    }

    Sound_MaybeSetActiveSdat(previousSdat);
    Os_RestoreIrq(irqState);
}
