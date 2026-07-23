/*
PURPOSE: Destroys a thread and wakes anything waiting for it to finish.
The argument is the thread to destroy.
The current thread is disposed through the dedicated current-thread path.
Other threads are detached, marked terminated, and followed by a reschedule.
*/
typedef unsigned int u32;

typedef struct OsThread OsThread;

typedef struct {
    OsThread *head;
    OsThread *tail;
} OsThreadQueue;

struct OsThread {
    unsigned char context[0x64];
    int state;
    unsigned char fields[0x34];
    OsThreadQueue joinQueue;
};

typedef struct {
    u32 schedulerState;
    OsThread *currentThread;
} OsThreadContext;

extern OsThreadContext data_0216ff5c;

extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 state);
extern void Os_DisposeCurrentThreadImpl(void);
extern u32 Os_DisableScheduler(void);
extern void Os_UnlockAllMutexes(OsThread *thread);
extern void Os_Thread_CancelAlarmForSleep(OsThread *thread);
extern void Os_PopThread(OsThread *thread);
extern void Os_Thread_WakeUp(OsThreadQueue *queue);
extern u32 Os_EnableScheduler(void);
extern void Os_RescheduleThread(void);

void func_0200e0ec(OsThread *thread)
{
    u32 previousIrqState = Os_DisableIrq();

    if (data_0216ff5c.currentThread == thread) {
        Os_DisposeCurrentThreadImpl();
    }

    (void)Os_DisableScheduler();
    Os_UnlockAllMutexes(thread);
    Os_Thread_CancelAlarmForSleep(thread);
    Os_PopThread(thread);

    thread->state = 2;
    Os_Thread_WakeUp(&thread->joinQueue);

    (void)Os_EnableScheduler();
    Os_RestoreIrq(previousIrqState);
    Os_RescheduleThread();
}
