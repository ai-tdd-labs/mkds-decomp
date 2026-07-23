// PURPOSE: Reads a file into a buffer of the expected size.
// The path and destination buffer select the file and its output location.
// A nonzero mode probably selects a 0x200-byte file and skips a 0x20-byte header.
// It returns zero when the file is missing or has the wrong length.

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
} FSFile;

extern void Fs_File_Initialize(FSFile *f);
extern int Fs_File_Open(FSFile *f, const char *path);
extern int Fs_File_Read(FSFile *f, void *buffer, unsigned int size);
extern void Fs_File_Close(FSFile *f);

int SomeFileRead_from_thumb(const char *path, void *buffer, int mode)
{
    FSFile file;
    unsigned int size;

    if (mode != 0) {
        size = 0x200;
    } else {
        size = 0x20;
    }

    if (mode != 0) {
        buffer = (char *)buffer + 0x20;
    }

    if (path == 0) {
        return 0;
    }

    Fs_File_Initialize(&file);
    if (Fs_File_Open(&file, path) == 0) {
        return 0;
    }

    if (size != (unsigned int)(file.field_28 - file.field_24)) {
        Fs_File_Close(&file);
        return 0;
    }

    Fs_File_Read(&file, buffer, size);
    Fs_File_Close(&file);
    return 1;
}
