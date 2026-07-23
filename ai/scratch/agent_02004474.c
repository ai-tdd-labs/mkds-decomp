// PURPOSE: Runs a file's queued async operation, and keeps running follow-up operations from its archive until none are left.
// Argument is a file/operation object (may be NULL). For each operation: mark it started (flag 0x40),
// if it is a blocking one (flag 4) wake the waiting thread and stop; otherwise mark it running (flag 8),
// execute it, and if it went asynchronous (result == 6) stop; otherwise fetch the archive's next
// operation and loop. Flags word is probably shared with interrupt handlers (volatile, IRQ window).

typedef unsigned int u32;

typedef struct FsFile {
    unsigned char _00[8];
    void *arc;               // +0x08: owning archive
    u32 volatile flags;      // +0x0c: state flags (0x40 started, 8 running, 4 blocking)
    u32 command;             // +0x10: second argument for the execute call
    unsigned char _14[4];
    unsigned char queue[4];  // +0x18: thread queue for blocking waiters
} FsFile;

extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 state);
extern void Os_Thread_WakeUp(void *queue);
extern int Fs_File_DoExecuteOperation(FsFile *file, u32 command);
extern FsFile *Fs_Archive_HandleNextOperation(void *archive);

void Fs_File_ExecuteAsyncOperation(FsFile *file)
{
    void *arc;
    u32 irq;
    int zero;
    int one;
    int blocking;

    arc = file->arc; // archive of the FIRST file only (loop-invariant); ROM loads this before the NULL check
    if (file == 0) {
        return;
    }
    zero = 0;
    one = 1;
    do {
        irq = Os_DisableIrq();
        file->flags |= 0x40;
        blocking = (file->flags & 4) ? one : zero; // materialized via hoisted 1/0 regs
        if (blocking) {
            Os_Thread_WakeUp(file->queue);
            Os_RestoreIrq(irq);
            return;
        }
        file->flags |= 8;
        Os_RestoreIrq(irq);
        if (Fs_File_DoExecuteOperation(file, file->command) == 6) {
            return;
        }
        file = Fs_Archive_HandleNextOperation(arc);
    } while (file != 0);
}
