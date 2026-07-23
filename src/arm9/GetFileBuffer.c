// PURPOSE: Gets the byte buffer location for an opened file.
// The path probably names a file stored in the game's file system.
// It opens the file, returns its archive base plus its current offset, and closes it.

typedef struct FSArchive {
    char _00[0x64];
    int field_64;
} FSArchive;

typedef struct FSFile {
    int field_00;
    int field_04;
    FSArchive *field_08;
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
} FSFile;

extern void Fs_File_Initialize(FSFile *f);
extern int Fs_File_Open(FSFile *f, const char *path);
extern void Fs_File_Close(FSFile *f);

int GetFileBuffer(const char *path)
{
    FSFile file;
    int result = 0;

    Fs_File_Initialize(&file);
    if (Fs_File_Open(&file, path) != 0) {
        result = file.field_08->field_64 + file.field_24;
        Fs_File_Close(&file);
    }

    return result;
}
