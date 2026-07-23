// PURPOSE: Waits until a thread has finished running.
// The thread argument probably contains its current state and a sleep queue.
// Interrupts are disabled while the state is checked and restored before return.

typedef unsigned int u32;

typedef struct OsThread {
    char _00[0x64];
    int state;
    char _68[0x34];
    int joinQueue;
} OsThread;

extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 irqState);
extern void Os_Thread_Sleep(void *queue);

void Os_Thread_Join(OsThread *thread)
{
    u32 irqState = Os_DisableIrq();

    if (thread->state != 2) {
        Os_Thread_Sleep(&thread->joinQueue);
    }

    Os_RestoreIrq(irqState);
}
