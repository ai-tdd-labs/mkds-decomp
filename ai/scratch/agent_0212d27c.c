// PURPOSE: Reads a range from a sound archive file into a buffer.
// The file index selects a FAT entry, while offset and size select its byte range.
// The requested size is clamped to the entry end before the file is read.

typedef struct FSFile {
    unsigned char _00[0x50];
} FSFile;

typedef struct SoundFileEntry {
    unsigned int start;
    unsigned int end;
    unsigned int _08;
    unsigned int _0C;
} SoundFileEntry;

typedef struct SoundFileTable {
    unsigned char _00[8];
    unsigned int count;
    SoundFileEntry entries[];
} SoundFileTable;

typedef struct SoundState {
    unsigned char _00[0x34];
    FSFile file_34;
    SoundFileTable *table_84;
} SoundState;

extern SoundState *data_0217dec4;
extern int Fs_File_Seek(FSFile *file, unsigned int offset, int origin);
extern int Fs_File_Read(FSFile *file, void *buffer, unsigned int size);

int Sound_ReadFile(unsigned int fileId, void *buffer, unsigned int size,
                   unsigned int offset)
{
    SoundState *state = data_0217dec4;

    if (fileId >= state->table_84->count) {
        return -1;
    }

    if (size > state->table_84->entries[fileId].end - offset) {
        size = state->table_84->entries[fileId].end - offset;
    }

    if (Fs_File_Seek(&state->file_34,
                     state->table_84->entries[fileId].start + offset, 0) == 0) {
        return -1;
    }

    return Fs_File_Read(&state->file_34, buffer, size);
}
