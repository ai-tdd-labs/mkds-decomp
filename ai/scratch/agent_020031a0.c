/* PURPOSE: Finishes a file operation and wakes its waiting thread.
 * The first argument is the file whose active operation has completed.
 * The second argument is the operation result stored for the waiting caller.
 * Interrupts stay disabled while the file is unlinked and its state is updated. */

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct FsFile FsFile;

typedef struct FsFileLink {
    FsFile *previous;
    FsFile *next;
} FsFileLink;

struct FsFile {
    FsFileLink link;       /* 0x00 */
    void *archive;         /* 0x08 */
    u32 status;            /* 0x0c */
    u32 command;           /* 0x10 */
    u32 operationResult;   /* 0x14 */
    u8 threadQueue[8];     /* 0x18 */
};

extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 irqState);
extern void Os_Thread_WakeUp(void *threadQueue);

void Fs_File_ReleaseOperation(FsFile *file, u32 operationResult)
{
    u32 irqState = Os_DisableIrq();
    FsFile *const previous = file->link.previous;
    FsFile *const next = file->link.next;

    if (previous != 0) {
        previous->link.next = next;
    }
    if (next != 0) {
        next->link.previous = previous;
    }

    /* Clear both links while preserving the original SDK assignment order. */
    file->link.next = file->link.previous = 0;
    file->status &= ~0x4f;
    file->operationResult = operationResult;
    Os_Thread_WakeUp(file->threadQueue);
    Os_RestoreIrq(irqState);
}
