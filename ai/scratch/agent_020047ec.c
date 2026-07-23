// PURPOSE: Changes the current filesystem directory to a path.
// The path is resolved through a temporary file object.
// On success, the resolved directory state is stored for later file access.
// It probably returns zero when the path cannot be found.

typedef struct FSFile {
    int field_00;
    int field_04;
    int field_08;
    int field_0c;
    int field_10;
    int field_14;
    int field_18;
    int field_1c;
    int field_20;
    int field_24;
    int field_28;
    int field_2c;
    int field_30;
    int field_34;
    int field_38;
    int field_3c;
    int field_40;
    int field_44;
    int field_48;
} FSFile;

typedef struct FsDirectoryState {
    int field_00;
    int field_04;
    int field_08;
} FsDirectoryState;

extern void Fs_File_Initialize(FSFile *f);
extern int Fs_File_FindPath(FSFile *f, const char *path, int unused,
                            FsDirectoryState *state);
extern FsDirectoryState data_0216f344;

int Fs_Chdir(const char *path)
{
    FsDirectoryState state;
    FSFile file;

    Fs_File_Initialize(&file);
    if (Fs_File_FindPath(&file, path, 0, &state) == 0) {
        return 0;
    }

    data_0216f344 = state;
    return 1;
}
