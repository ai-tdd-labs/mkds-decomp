/*
PURPOSE: Opens a file and reads it into a buffer when it fits.
Probably receives a file path, destination buffer, and requested byte count.
It returns whether the file opened and the read did not fail.
*/

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

int OpenReadFileBufferSize_from_thumb(const char *path, void *buffer,
                                      unsigned int size)
{
    FSFile file;
    int result;

    Fs_File_Initialize(&file);
    result = Fs_File_Open(&file, path);
    if (result != 0) {
        if (size <= (unsigned int)(file.field_28 - file.field_24)) {
            if (Fs_File_Read(&file, buffer, size) < 0) {
                result = 0;
            }
            Fs_File_Close(&file);
        }
    }

    return result;
}
