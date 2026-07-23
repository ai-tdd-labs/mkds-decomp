// PURPOSE: Loads sound data from a file path.
// The destination holds the opened file and the resulting sound archive state.
// It probably marks that archive as active after a successful load.

typedef struct FsFileId {
    int word0;
    int word1;
} FsFileId;

typedef struct FSFile {
    int field_00;
    int field_04;
    int field_08;
    int field_0c;
    int field_10;
    int pad_14;
    int field_18;
    int field_1c;
} FSFile;

typedef struct SoundState {
    char _00[0x30];
    int ownsFile;
    FSFile file_34;
    char _54[0x28];
    FsFileId fileId_7c;
    int field_84;
    int field_88;
    int field_8c;
} SoundState;

extern int Fs_FileId_LoadFromPath(FsFileId *fileId, const char *path);
extern void Fs_File_Initialize(FSFile *f);
extern int Fs_File_OpenById(FSFile *file, FsFileId fileId);
extern int Sound_ReadSdatFromOpenedFile(SoundState *state, void *heap,
                                        int flags, int ownsFile);
extern void Sound_MaybeSetActiveSdat(void *sdat);

int Sound_ReadSdatFromPathImplV2(SoundState *state, const char *path,
                                 void *heap, int flags)
{
    state->field_8c = 0;
    state->field_84 = 0;
    state->field_88 = 0;

    if (!Fs_FileId_LoadFromPath(&state->fileId_7c, path)) {
        return 0;
    }

    Fs_File_Initialize(&state->file_34);
    if (!Fs_File_OpenById(&state->file_34, state->fileId_7c)) {
        return 0;
    }

    state->ownsFile = 1;
    if (!Sound_ReadSdatFromOpenedFile(state, heap, flags, 1)) {
        return 0;
    }

    Sound_MaybeSetActiveSdat(state);
    return 1;
}
