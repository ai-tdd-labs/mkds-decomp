// PURPOSE: Wakes a thread so it can run again.
// The thread state is changed while interrupts are disabled.
// It then asks the scheduler to choose the next runnable thread.

typedef unsigned int u32;

typedef struct OsThread {
    char unused[0x64];
    u32 state;
} OsThread;

extern u32 Os_DisableIrq(void);
extern void Os_RescheduleThread(void);
extern void Os_RestoreIrq(u32 state);

void Os_Thread_WakeUpDirect(OsThread *thread)
{
    u32 irq = Os_DisableIrq();

    thread->state = 1;
    Os_RescheduleThread();
    Os_RestoreIrq(irq);
}
