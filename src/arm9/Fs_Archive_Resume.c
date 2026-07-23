// PURPOSE: Resumes an archive's pending file operation when it is paused.
// The archive argument probably stores its paused state in a flags word.
// Interrupts are disabled while the state is changed, then restored before
// the pending asynchronous operation is executed.

typedef unsigned int u32;

typedef struct FsArchive {
    unsigned char _00[0x1c];
    u32 flags;
} FsArchive;

extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 state);
extern void *Fs_Archive_HandleNextOperation(FsArchive *archive);
extern void Fs_File_ExecuteAsyncOperation(void *operation);

int Fs_Archive_Resume(FsArchive *archive)
{
    void *operation = 0;
    u32 irqState;
    int paused;
    int wasNotPaused;

    irqState = Os_DisableIrq();
    paused = !!(archive->flags & 8);
    if (paused == 0) {
        wasNotPaused = 1;
    } else {
        wasNotPaused = 0;
    }
    if (wasNotPaused != 0) {
        goto restore;
    } else {
        archive->flags &= ~8;
        operation = Fs_Archive_HandleNextOperation(archive);
    }

restore:
    Os_RestoreIrq(irqState);
    if (operation != 0) {
        Fs_File_ExecuteAsyncOperation(operation);
    }

    return wasNotPaused;
}
