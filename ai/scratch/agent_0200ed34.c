// PURPOSE: Waits until the current thread can lock a mutex.
// It records the current thread as the owner when the mutex becomes free.
// A thread that already owns the mutex can lock it again.
// Other threads probably sleep on the mutex until it is available.

typedef unsigned int u32;

typedef struct OsThread {
    unsigned char unknown00[0x84];
    void *queue;
} OsThread;

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
extern void Os_Thread_Sleep(void *queue);

void Os_Mutex_Lock(OsMutex *mutex)
{
    u32 previousIrqState;
    OsThread *currentThread;
    void *zero;

    previousIrqState = Os_DisableIrq();
    currentThread = data_0216ff5c.currentThread;
    zero = 0;

    while (1) {
        if (mutex->owner == 0) {
            mutex->owner = currentThread;
            mutex->lockCount++;
            Os_Mutex_EnqueueThread(currentThread, mutex);
            break;
        }

        if (mutex->owner == currentThread) {
            mutex->lockCount++;
            break;
        }

        currentThread->queue = mutex;
        Os_Thread_Sleep(mutex);
        currentThread->queue = zero;
    }

    Os_RestoreIrq(previousIrqState);
}
