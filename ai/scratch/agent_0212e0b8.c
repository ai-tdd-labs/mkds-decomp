// PURPOSE: Prepares a sound wave archive table for playback.
// The file ID selects the archive and the context owns new memory.
// Existing loaded data is returned without reading the file again.
// The option probably registers newly loaded data with the active archive.

typedef signed int s32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct SoundContext SoundContext;

typedef struct SoundWaveArchive {
    u8 header[0x38];
    u32 waveCount;
    u32 waveOffsets[];
} SoundWaveArchive;

typedef void (*SoundDisposeCallback)(void *payload, u16 payloadSize,
                                     void *soundArchive, u32 customArgument);

extern SoundWaveArchive data_0217dec8;
extern void *Sound_MaybeGetRawFilePointer(u32 fileId);
extern s32 Sound_ReadFile(u32 fileId, void *buffer, u32 size, u32 offset);
extern void *Sound_GetActiveSdat(void);
extern void *Sound_Context_Allocate(SoundContext *context,
                                    unsigned int payloadSize,
                                    SoundDisposeCallback disposeCallback,
                                    void *soundArchive,
                                    void *customArgument);
extern void Sound_DtorFn_SwarHeader(void *payload, u16 payloadSize,
                                    void *soundArchive, u32 customArgument);
extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);
extern void Mem_CpuFill8(void *destination, u32 value, u32 size);
extern void DC_SomeClean(void *buffer, u32 size);
extern void Sound_SetFileFatDynamicOffsetField(u32 fileId, void *rawFile);

void *Sound_PrepareSwarDataImpl(u32 fileId, SoundContext *context,
                                int useActiveSdat)
{
    SoundWaveArchive *rawFile;
    u32 archiveSize;
    u32 waveTableSize;
    s32 readSize;

    rawFile = (SoundWaveArchive *)Sound_MaybeGetRawFilePointer(fileId);
    if (rawFile == 0) {
        readSize = Sound_ReadFile(fileId, &data_0217dec8,
                                  sizeof(data_0217dec8), 0);
        if (readSize != sizeof(data_0217dec8)) {
            return 0;
        }

        waveTableSize = sizeof(u32) * data_0217dec8.waveCount;
        archiveSize = sizeof(data_0217dec8) + waveTableSize * 2;

        if (context == 0) {
            return 0;
        }

        rawFile = (SoundWaveArchive *)Sound_Context_Allocate(
            context, archiveSize + 0x20, Sound_DtorFn_SwarHeader,
            useActiveSdat ? Sound_GetActiveSdat() : 0, (void *)fileId);
        if (rawFile == 0) {
            return 0;
        }

        if (Sound_ReadFile(fileId, rawFile,
                           sizeof(data_0217dec8) + waveTableSize, 0) !=
            sizeof(data_0217dec8) + waveTableSize) {
            return 0;
        }

        Mem_CpuCopy8(rawFile->waveOffsets,
                     &rawFile->waveOffsets[rawFile->waveCount],
                     waveTableSize);
        Mem_CpuFill8(rawFile->waveOffsets, 0, waveTableSize);

        DC_SomeClean(rawFile, archiveSize);

        if (useActiveSdat) {
            Sound_SetFileFatDynamicOffsetField(fileId, rawFile);
        }
    }

    return rawFile;
}
