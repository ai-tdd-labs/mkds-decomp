// PURPOSE: Initializes the main sound data used by the game.
// This routine has no arguments and returns whether every required sound resource loaded.
// It probably redirects shared archive and wave files before completing the sound setup.
// Any failed load stops initialization and returns zero.

typedef unsigned int u32;

typedef struct SoundSarcInfoEntry {
    u32 fileId;
} SoundSarcInfoEntry;

typedef struct SoundSwarInfoEntry {
    u32 fileId : 24;
    u32 flags : 8;
} SoundSwarInfoEntry;

typedef struct SoundFileList {
    u32 files[16];
    int count;
} SoundFileList;

extern unsigned char data_0217c868[];
extern void *data_0217d130;
extern unsigned char data_0217d0a0[];
extern const char data_0216cb30[];
extern SoundFileList data_0217d178;

extern void Sound_MaybeSetActiveSdat(void *sdat);
extern int Sound_ReadSdatFromPathImplV2(void *destination, const char *path,
                                       void *heap, int flags);
extern void SetGlobalSdatUsed(int used);
extern int Sound_LoadSarc(int archiveId, void *heap);
extern SoundSarcInfoEntry *Sound_GetSarcInfoEntry(int archiveId);
extern u32 Sound_MaybeGetRawFilePointer(u32 fileId);
extern void Sound_SetFileFatDynamicOffsetField(u32 fileId, u32 offset);
extern int Sound_LoadSwar(int waveArchiveId, void *heap);
extern SoundSwarInfoEntry *Sound_GetSwarInfoEntry(int waveArchiveId);
extern int Sound_LoadSbnkWithFlags(int bankId, int flags, void *heap);
extern int func_0210ed20(int first, int second);
extern void func_02108950(void);
extern void func_0210e4c8(void);

int Maybe_data_Sound_sound_data(void)
{
    int loaded;
    SoundSarcInfoEntry *redirectSourceArchive;
    SoundSarcInfoEntry *redirectTargetArchive;
    SoundSwarInfoEntry *redirectSourceWave;
    SoundSwarInfoEntry *redirectTargetWave;
    u32 sourceFileId;
    u32 targetFileId;

    Sound_MaybeSetActiveSdat(data_0217c868);
    loaded = Sound_ReadSdatFromPathImplV2(data_0217d0a0, data_0216cb30,
                                          data_0217d130, 0);
    SetGlobalSdatUsed(1);
    if (!loaded) {
        return 0;
    }

    if (!Sound_LoadSarc(1, data_0217d130)) {
        return 0;
    }

    redirectSourceArchive = Sound_GetSarcInfoEntry(1);
    redirectTargetArchive = Sound_GetSarcInfoEntry(0);
    sourceFileId = redirectSourceArchive->fileId;
    targetFileId = redirectTargetArchive->fileId;

    /* Make archive zero reuse archive one's loaded data. */
    Sound_SetFileFatDynamicOffsetField(
        targetFileId, Sound_MaybeGetRawFilePointer(sourceFileId));
    Sound_SetFileFatDynamicOffsetField(sourceFileId, 0);
    data_0217d178.files[data_0217d178.count++] = targetFileId;

    if (Sound_LoadSwar(0x3e, data_0217d130)) {
        redirectSourceWave = Sound_GetSwarInfoEntry(0x3e);
        redirectTargetWave = Sound_GetSwarInfoEntry(0x3d);
        sourceFileId = redirectSourceWave->fileId;
        targetFileId = redirectTargetWave->fileId;

        /* Apply the same redirection to the paired wave archives. */
        Sound_SetFileFatDynamicOffsetField(
            targetFileId, Sound_MaybeGetRawFilePointer(sourceFileId));
        Sound_SetFileFatDynamicOffsetField(sourceFileId, 0);
        data_0217d178.files[data_0217d178.count++] = targetFileId;
        loaded = 1;
    } else {
        loaded = 0;
    }
    if (!loaded) {
        return 0;
    }

    if (Sound_LoadSwar(1, data_0217d130)) {
        if (Sound_LoadSbnkWithFlags(0, 2, data_0217d130)) {
            if (Sound_LoadSarc(0, data_0217d130)) {
                loaded = 1;
            } else {
                loaded = 0;
            }
        } else {
            loaded = 0;
        }
    } else {
        loaded = 0;
    }
    if (!loaded) {
        return 0;
    }

    if (!func_0210ed20(1, 1)) {
        return 0;
    }

    func_02108950();
    func_0210e4c8();
    return 1;
}
