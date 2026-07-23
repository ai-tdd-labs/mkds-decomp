// PURPOSE: Reads bytes from a file into a caller-provided buffer.
// The requested byte count is clipped to the unread portion of the file.
// Synchronous reads wait for completion and return the actual bytes read.

typedef unsigned int u32;
typedef int s32;
typedef int BOOL;

typedef struct FsFile FsFile;

typedef struct FsFileRange {
    u32 ownId;
    u32 top;
    u32 bottom;
    u32 position;
} FsFileRange;

typedef struct FsFileReadInfo {
    void *destination;
    u32 originalLength;
    u32 length;
} FsFileReadInfo;

struct FsFile {
    unsigned char padding00[0x0c];
    u32 status;
    unsigned char padding10[0x10];
    FsFileRange file;
    FsFileReadInfo read;
};

extern BOOL Fs_File_SendOperation(FsFile *file, int operation);
extern BOOL Fs_File_WaitAsync(FsFile *file);

s32 Fs_File_DoRead(FsFile *file, void *destination, s32 length, BOOL asynchronous)
{
    const s32 position = (s32)file->file.position;
    const s32 remaining = (s32)(file->file.bottom - position);
    const u32 originalLength = (u32)length;

    if (length > remaining) {
        length = remaining;
    }
    if (length < 0) {
        length = 0;
    }
    file->read.destination = destination;
    file->read.originalLength = originalLength;
    file->read.length = (u32)length;
    if (!asynchronous) {
        file->status |= 4;
    }
    (void)Fs_File_SendOperation(file, 0);
    if (!asynchronous) {
        if (Fs_File_WaitAsync(file)) {
            length = (s32)(file->file.position - position);
        } else {
            length = -1;
        }
    }
    return length;
}
