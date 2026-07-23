// PURPOSE: Disposes the currently running thread.
/*
 * The scheduler is stopped while the current thread is detached.
 * Its mutexes are released, waiters are woken, and scheduling resumes.
 * The final termination call probably never returns.
 */

typedef struct OSThread OSThread;

typedef struct OSThreadQueue {
    char padding[0];
} OSThreadQueue;

struct OSThread {
    char padding_00[0x64];
    int state;
    char padding_68[0x34];
    OSThreadQueue queue;
};

extern OSThread **data_0216ff54;
extern void Os_DisableScheduler(void);
extern void Os_UnlockAllMutexes(OSThread *thread);
extern void Os_PopThread(OSThread *thread);
extern void Os_Thread_WakeUp(OSThreadQueue *queue);
extern void Os_EnableScheduler(void);
extern void Os_RescheduleThread(void);
extern void Os_Terminate(void);

void Os_DisposeCurrentThreadImpl(void)
{
    OSThread *thread = *data_0216ff54;

    Os_DisableScheduler();
    Os_UnlockAllMutexes(thread);
    Os_PopThread(thread);
    thread->state = 2;
    Os_Thread_WakeUp(&thread->queue);
    Os_EnableScheduler();
    Os_RescheduleThread();
    Os_Terminate();
}
