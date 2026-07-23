// PURPOSE: Suspends an archive until its current work can safely stop.
// The archive probably stores state flags and a thread sleep queue.
// Interrupts protect the state change while an active operation finishes.

typedef unsigned int u32;

typedef struct FsArchive {
    unsigned char _00[0x14];
    unsigned char threadQueue[8];
    volatile u32 flags;
} FsArchive;

extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 state);
extern void Os_Thread_Sleep(void *queue);

int Fs_Archive_Suspend(FsArchive *archive)
{
    u32 irqState;
    int result;

    irqState = Os_DisableIrq();
    result = ((archive->flags & 8) ? 1 : 0) == 0;
    if (result) {
        if ((archive->flags & 0x10) != 0) {
            archive->flags |= 0x40;
            do {
                Os_Thread_Sleep(&archive->threadQueue);
            } while ((archive->flags & 0x40) != 0);
        } else {
            archive->flags |= 8;
        }
    }
    Os_RestoreIrq(irqState);
    return result;
}
