// PURPOSE: Opens a file using its path.
// The file object receives the opened file state.
// The path is probably converted to an internal two-word file identifier first.

typedef struct FsFileId {
    int word0;
    int word1;
} FsFileId;

extern int Fs_FileId_LoadFromPath(FsFileId *fileId, const char *path);
extern int Fs_File_OpenById(void *file, FsFileId fileId);

int Fs_File_Open(void *file, const char *path)
{
    FsFileId fileId;

    if (Fs_FileId_LoadFromPath(&fileId, path) != 0) {
        if (Fs_File_OpenById(file, fileId) != 0) {
            return 1;
        }
    }
    return 0;
}
