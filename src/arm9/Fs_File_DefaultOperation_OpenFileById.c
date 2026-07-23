// PURPOSE: Opens a file from its numeric archive ID.
// The argument is the file object that receives the opened file range.
// It probably reads the selected archive-table entry before starting operation 7.

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct FsArchive {
    u8 pad_00[0x2c];
    void *fileAllocationTable; /* 0x2c */
    u32 fileCount;             /* 0x30 */
} FsArchive;

typedef struct FsFile {
    u8 pad_00[8];
    FsArchive *archive;        /* 0x08 */
    u8 pad_0c[0x24];
    u32 rangeStart;            /* 0x30 */
    u32 fileId;                /* 0x34, input file ID on entry */
    u32 rangeFileId;           /* 0x38 */
} FsFile;

typedef struct FsSyncReader {
    FsArchive *archive;
    void *position;
} FsSyncReader;

typedef struct FsFileRange {
    u32 start;
    u32 end;
} FsFileRange;

extern void Fs_SyncReader_Read(FsSyncReader *reader, FsFileRange *range, u32 size);
extern int Fs_File_DoExecuteOperation(FsFile *file, u32 operation);

int Fs_File_DefaultOperation_OpenFileById(FsFile *file)
{
    FsFileRange range;
    FsSyncReader reader;
    u32 fileId = file->fileId;

    if ((fileId << 3) >= file->archive->fileCount) {
        return 1;
    }

    reader.archive = file->archive;
    reader.position = (u8 *)reader.archive->fileAllocationTable + (fileId << 3);
    Fs_SyncReader_Read(&reader, &range, 8);

    file->rangeStart = range.start;
    file->fileId = range.end;
    file->rangeFileId = fileId;
    return Fs_File_DoExecuteOperation(file, 7);
}
