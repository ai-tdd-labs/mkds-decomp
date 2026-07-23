// PURPOSE: Puts the current thread to sleep until its queue wakes it.
// The optional queue receives the current thread before scheduling changes.
// Interrupt state is saved and restored around the scheduler update.
// The exact thread-state field meanings are probably internal OS details.

typedef unsigned int u32;

typedef struct Os_Thread {
    unsigned char unknown00[0x64];
    int state;
    unsigned char unknown68[0x10];
    void *queue;
} Os_Thread;

typedef struct OsThreadContext {
    Os_Thread *currentThread;
} OsThreadContext;

extern OsThreadContext *data_0216ff54;
extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 irqState);
extern void Os_ThreadQueue_Queue(void *queue, Os_Thread *thread);
extern void Os_RescheduleThread(void);

void Os_Thread_Sleep(void *queue)
{
    u32 irqState = Os_DisableIrq();
    Os_Thread *thread = data_0216ff54->currentThread;

    if (queue != 0) {
        thread->queue = queue;
        Os_ThreadQueue_Queue(queue, thread);
    }

    thread->state = 0;
    Os_RescheduleThread();
    Os_RestoreIrq(irqState);
}
