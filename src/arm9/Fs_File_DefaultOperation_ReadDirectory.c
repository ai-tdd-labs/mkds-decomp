// PURPOSE: Reads the next file or folder from an open directory.
// The argument is the directory file object and supplies the output entry.
// It reads the entry name unless the caller only wants to advance the listing.
// Folder entries receive a directory position; file entries receive a file ID.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct FsArchive FsArchive;

typedef struct FsDirectoryPosition {
    FsArchive *archive;
    u16 ownId;
    u16 index;
    u32 position;
} FsDirectoryPosition;

typedef struct FsDirectoryEntry {
    FsArchive *archive;
    union {
        u32 fileId;
        struct {
            u16 ownId;
            u16 index;
        } directory;
    } id;
    u32 position;
    u32 isDirectory;
    u32 nameLength;
    char name[128];
} FsDirectoryEntry;

typedef struct FsFile {
    u8 pad_00[8];
    FsArchive *archive;
    u8 pad_0c[0x14];
    FsDirectoryPosition current;
    u32 parent;
    union {
        struct {
            FsDirectoryEntry *entry;
            u32 skipName;
        } readDirectory;
        u8 raw[0x18];
    } argument;
} FsFile;

typedef struct FsSyncReader {
    FsArchive *archive;
    void *position;
} FsSyncReader;

extern void Fs_SyncReader_Read(FsSyncReader *reader, void *destination, u32 size);

int Fs_File_DefaultOperation_ReadDirectory(FsFile *file)
{
    FsDirectoryEntry *entry = file->argument.readDirectory.entry;
    FsSyncReader reader;

    reader.archive = file->archive;
    reader.position = (void *)file->current.position;

    {
        u8 descriptor;

        Fs_SyncReader_Read(&reader, &descriptor, sizeof(descriptor));
        entry->nameLength = (u32)(descriptor & 0x7f);
        entry->isDirectory = (u32)((descriptor >> 7) & 1);
    }

    if (entry->nameLength == 0) {
        return 1;
    }

    if (!file->argument.readDirectory.skipName) {
        Fs_SyncReader_Read(&reader, entry->name, entry->nameLength);
        entry->name[entry->nameLength] = '\0';
    } else {
        reader.position = (u8 *)reader.position + entry->nameLength;
    }

    if (entry->isDirectory) {
        u16 id;

        Fs_SyncReader_Read(&reader, &id, sizeof(id));
        entry->archive = file->archive;
        entry->id.directory.ownId = (u16)(id & 0xfff);
        entry->id.directory.index = 0;
        entry->position = 0;
    } else {
        entry->archive = file->archive;
        entry->id.fileId = file->current.index;
        ++file->current.index;
    }

    file->current.position = (u32)reader.position;
    return 0;
}
