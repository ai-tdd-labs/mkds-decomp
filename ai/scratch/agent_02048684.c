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

int OpenReadEntireFileBuffer_from_thumb(const char *path, void *buffer,
                                        unsigned int size)
{
    // PURPOSE: Opens a file and reads all of it into a buffer.
    FSFile file;
    int result;
    unsigned int fileSize;

    Fs_File_Initialize(&file);
    result = Fs_File_Open(&file, path);
    if (result != 0) {
        fileSize = (unsigned int)(file.field_28 - file.field_24);
        if (size == 0 || fileSize <= size) {
            if (Fs_File_Read(&file, buffer, fileSize) < 0) {
                result = 0;
            }
            Fs_File_Close(&file);
        } else {
            result = 0;
        }
    }

    return result;
}
