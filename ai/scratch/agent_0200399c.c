// PURPOSE: Moves a directory listing to the position saved in the file object.
// The argument is the file object whose seek-directory request (at +0x30) holds
// the target directory position. It reads that directory's 8-byte name-table
// entry from the archive, copies the requested position into the current-read
// state (at +0x20), and when the request points at the directory start it also
// records the first file ID and the entry-name data address. The parent
// directory ID is masked to 12 bits. Always returns 0 (success).

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct FsArchive {
    u8 pad_00[0x34];
    void *fnt; /* 0x34, filename table base */
} FsArchive;

/* Directory position: table index plus a resume position within the entry list. */
typedef struct FsDirPos {
    u32 pos;   /* +0x0, current entry address (0 = start of directory) */
    u16 index; /* +0x4, directory table index */
    u16 f6;    /* +0x6, probably current file ID */
    u32 f8;    /* +0x8, probably resume read address */
} FsDirPos;

typedef struct FsFile {
    u8 pad_00[8];
    FsArchive *archive; /* 0x08 */
    u8 pad_0c[0x14];
    FsDirPos current;   /* 0x20, active read position */
    u32 parent;         /* 0x2c, parent directory ID (12 bits) */
    FsDirPos pos;       /* 0x30, requested seek position */
} FsFile;

/* 8-byte FNT directory entry. */
typedef struct FsDirEntry {
    u32 start; /* +0x0, offset of the entry names within the table */
    u16 id;    /* +0x4, ID of the first file in the directory */
    u16 top;   /* +0x6, parent directory ID (low 12 bits) */
} FsDirEntry;

typedef struct FsSyncReader {
    FsArchive *archive;
    void *position;
} FsSyncReader;

extern void Fs_SyncReader_Read(FsSyncReader *reader, FsDirEntry *entry, u32 size);

int Fs_File_DefaultOperation_SeekDirectory(FsFile *file)
{
    FsDirEntry entry;    /* sp+0x0 */
    FsSyncReader reader; /* sp+0x8 */
    FsArchive *arch = file->archive; /* r5 */
    FsDirPos *pos = &file->pos;      /* r4, cached base for the request block */

    reader.archive = arch;
    reader.position = (u8 *)arch->fnt + (pos->index << 3);
    Fs_SyncReader_Read(&reader, &entry, 8);

    /* Adopt the requested position as the current one (12-byte block copy). */
    file->current = *pos;

    /* Seeking to the directory start: derive ID and address from the entry. */
    if (pos->f6 == 0 && pos->f8 == 0) {
        file->current.f6 = entry.id;
        file->current.f8 = (u32)arch->fnt + entry.start;
    }
    file->parent = entry.top & 0xfff; /* pool constant, not mov-encodable */
    return 0;
}
