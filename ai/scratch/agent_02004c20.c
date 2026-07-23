// PURPOSE: Resolves a path to a file or directory in a mounted archive.
// The path may start at the current directory, the archive root, or a named mount.
// The file object receives the chosen archive, starting position, and remaining path.
// Exactly one of the file-ID and directory-position outputs is selected.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct FsArchive {
    u8 pad_00[0x1c];
    u32 flags;
} FsArchive;

typedef struct FsDirectoryPosition {
    FsArchive *archive;
    u16 ownId;
    u16 index;
    u32 position;
} FsDirectoryPosition;

typedef struct FsFileId {
    FsArchive *archive;
    u32 fileId;
} FsFileId;

typedef struct FsFindPathInfo {
    FsDirectoryPosition position;
    const char *path;
    u32 findDirectory;
    void *result;
} FsFindPathInfo;

typedef struct FsFile {
    u8 pad_00[8];
    FsArchive *archive;
    u8 pad_0c[0x24];
    FsFindPathInfo findPath;
} FsFile;

extern FsArchive *Fs_FindArchiveByMountName(const char *mountName,
                                             int nameLength);
extern int Fs_File_SendOperation(FsFile *file, int operation);
extern FsDirectoryPosition data_0216f344;

static inline u8 Fs_ReadByte(const void *address)
{
    return *(const u8 *)address;
}

static inline int Fs_IsSlash(u32 c)
{
    return c == '/' || c == '\\';
}

static inline int Fs_IsArchiveLoaded(volatile const FsArchive *archive)
{
    return (archive->flags & 2) ? 1 : 0;
}

int Fs_File_FindPath(FsFile *file, const char *path, FsFileId *fileId,
                     FsDirectoryPosition *directory)
{
    FsDirectoryPosition position;

    if (Fs_IsSlash(Fs_ReadByte(path))) {
        position.archive = data_0216f344.archive;
        position.ownId = 0;
        position.position = 0;
        position.index = 0;
        path++;
    } else {
        int i;

        position = data_0216f344;
        for (i = 0; i <= 3; ++i) {
            u32 c = Fs_ReadByte(path + i);

            if (!c || Fs_IsSlash(c)) {
                break;
            } else if (c == ':') {
                FsArchive *const archive =
                    Fs_FindArchiveByMountName(path, i);

                if (!archive) {
                    return 0;
                } else if (!Fs_IsArchiveLoaded(archive)) {
                    return 0;
                }

                position.archive = archive;
                position.position = 0;
                position.index = 0;
                position.ownId = 0;
                path += i + 1;
                if (Fs_IsSlash(Fs_ReadByte(path))) {
                    ++path;
                }
                break;
            }
        }
    }

    file->archive = position.archive;
    file->findPath.path = path;
    file->findPath.position = position;
    if (directory) {
        file->findPath.findDirectory = 1;
        file->findPath.result = directory;
    } else {
        file->findPath.findDirectory = 0;
        file->findPath.result = fileId;
    }

    return Fs_File_SendOperation(file, 4);
}
