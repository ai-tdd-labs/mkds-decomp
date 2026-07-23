// PURPOSE: Completes a file operation and starts the next queued one.
// The file keeps its archive, command, and final operation result.
// The archive handler probably returns the next file that needs execution.

typedef unsigned int u32;

typedef struct FsFile FsFile;

struct FsFile {
    u32 previous;
    u32 next;
    void *archive;
    u32 status;
    u32 command;
    u32 operationResult;
};

extern u32 Fs_File_DoExecuteOperation(FsFile *file, u32 command);
extern void Fs_File_ReleaseOperation(FsFile *file, u32 operationResult);
extern FsFile *Fs_Archive_HandleNextOperation(void *archive);
extern void Fs_File_ExecuteAsyncOperation(FsFile *file);

int Fs_File_ExecuteSyncOperation(FsFile *file)
{
    FsFile *next;

    Fs_File_ReleaseOperation(file, Fs_File_DoExecuteOperation(file, file->command));
    next = Fs_Archive_HandleNextOperation(file->archive);
    if (next != 0) {
        Fs_File_ExecuteAsyncOperation(next);
    }
    return file->operationResult == 0;
}
