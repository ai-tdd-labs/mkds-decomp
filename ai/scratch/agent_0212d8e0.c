// PURPOSE: Loads sound archive data from a file path and makes it active on success.

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
extern void Fs_File_Initialize(FSFile *file);
extern int Fs_File_OpenById(FSFile *file, FsFileId fileId);
extern int Sound_ReadSdatFromOpenedFile(SoundState *state, void *heap,
                                        int flags, int ownsFile);
extern SoundState *data_0217dec4;

int Sound_ReadSdatFromPathImpl(SoundState *state, const char *path, void *heap,
                               int flags)
{
    int result;

    state->field_8c = 0;
    state->field_84 = 0;
    state->field_88 = 0;
    if (Fs_FileId_LoadFromPath(&state->fileId_7c, path) == 0) {
        return 0;
    }

    Fs_File_Initialize(&state->file_34);
    if (Fs_File_OpenById(&state->file_34, state->fileId_7c) == 0) {
        return 0;
    }

    state->ownsFile = 1;
    result = Sound_ReadSdatFromOpenedFile(state, heap, flags, 1);
    if (result != 0) {
        data_0217dec4 = state;
    }
    return result;
}
