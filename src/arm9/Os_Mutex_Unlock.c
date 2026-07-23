/*
PURPOSE: Releases a mutex held by the current thread.
The mutex is only changed when the current thread owns it.
Its recursive lock count is reduced, and waiting threads are woken when it reaches zero.
Interrupts are disabled while the mutex state is updated.
*/
typedef unsigned int u32;

typedef struct OsThread OsThread;

typedef struct {
    OsThread *head;
    OsThread *tail;
} OsThreadQueue;

typedef struct OsMutex {
    OsThreadQueue waitingThreads;
    OsThread *owner;
    int lockCount;
} OsMutex;

typedef struct {
    u32 state;
    OsThread *currentThread;
} OsThreadContext;

extern OsThreadContext data_0216ff5c;
extern u32 Os_DisableIrq(void);
extern u32 Os_RestoreIrq(u32 state);
extern void Os_Mutex_DequeueThread(OsThread *thread, OsMutex *mutex);
extern void Os_Thread_WakeUp(OsThreadQueue *queue);

void Os_Mutex_Unlock(OsMutex *mutex)
{
    u32 previousIrqState;
    OsThread *currentThread;

    previousIrqState = Os_DisableIrq();
    currentThread = data_0216ff5c.currentThread;

    if (mutex->owner == currentThread) {
        if (--mutex->lockCount == 0) {
            Os_Mutex_DequeueThread(currentThread, mutex);
            mutex->owner = 0;
            Os_Thread_WakeUp(&mutex->waitingThreads);
        }
    }

    (void)Os_RestoreIrq(previousIrqState);
}
