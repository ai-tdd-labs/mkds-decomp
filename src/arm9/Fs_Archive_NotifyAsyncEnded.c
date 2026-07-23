// PURPOSE: Notifies an archive that its asynchronous file operation has ended.
// The archive and completed operation result are supplied by the async path.
// A queued operation is started when one is available; otherwise its waiter is
// probably notified while interrupts protect the archive state.

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct FsFile FsFile;

struct FsFile {
    u8 unknown00[0x14];
    u32 operationResult;
};

typedef struct FsArchive {
    u8 unknown00[0x0c];
    u8 threadQueue[0x10];
    volatile u32 flags;
    u32 unknown20;
    FsFile *file;
} FsArchive;

extern void Fs_File_ReleaseOperation(FsFile *file, u32 operationResult);
extern FsFile *Fs_Archive_HandleNextOperation(FsArchive *archive);
extern void Fs_File_ExecuteAsyncOperation(FsFile *file);
extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 irqState);
extern void Os_Thread_WakeUp(void *threadQueue);

void Fs_Archive_NotifyAsyncEnded(FsArchive *archive, u32 operationResult)
{
    FsFile *file;
    u32 flags;
    u32 irqState;

    if (archive->flags & 0x100) {
        flags = archive->flags;
        file = archive->file;
        archive->flags = flags & ~0x100;
        Fs_File_ReleaseOperation(file, operationResult);
        file = Fs_Archive_HandleNextOperation(archive);
        if (file == 0) {
            return;
        }
        Fs_File_ExecuteAsyncOperation(file);
    } else {
        file = archive->file;
        irqState = Os_DisableIrq();
        file->operationResult = operationResult;
        archive->flags &= ~0x200;
        Os_Thread_WakeUp(archive->threadQueue);
        Os_RestoreIrq(irqState);
    }
}
