/*
PURPOSE: Tries to lock a mutex without waiting.
The mutex may be locked again by the thread that already owns it.
Returns one when the current thread acquires the mutex, or zero when another thread owns it.
Interrupts are disabled while the mutex state is inspected and updated.
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
extern void Os_RestoreIrq(u32 state);
extern void Os_Mutex_EnqueueThread(OsThread *thread, OsMutex *mutex);

int Os_Mutex_TryLock(OsMutex *mutex)
{
    u32 previousIrqState;
    int lockAcquired;
    OsThread *currentThread;

    previousIrqState = Os_DisableIrq();
    currentThread = data_0216ff5c.currentThread;

    if (mutex->owner == 0) {
        mutex->owner = currentThread;
        mutex->lockCount++;
        Os_Mutex_EnqueueThread(currentThread, mutex);
        lockAcquired = 1;
    } else if (mutex->owner == currentThread) {
        mutex->lockCount++;
        lockAcquired = 1;
    } else {
        lockAcquired = 0;
    }

    Os_RestoreIrq(previousIrqState);
    return lockAcquired;
}
