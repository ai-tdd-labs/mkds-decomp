// PURPOSE: Releases every mutex held by a thread.
// The thread owns a queue of mutexes starting at offset 0x88.
// Each removed mutex is probably made available before its waiting threads wake.

typedef struct OsThread OsThread;
typedef struct OsMutex OsMutex;

typedef struct {
    OsThread *head;
    OsThread *tail;
} OsThreadQueue;

typedef struct {
    OsMutex *head;
    OsMutex *tail;
} OsMutexQueue;

struct OsMutex {
    OsThreadQueue waitingThreads;
    OsThread *owner;
    int lockCount;
};

struct OsThread {
    char _00[0x88];
    OsMutexQueue mutexQueue;
};

extern OsMutex *Os_MutexQueue_Pop(OsMutexQueue *queue);
extern void Os_Thread_WakeUp(OsThreadQueue *queue);

void Os_UnlockAllMutexes(OsThread *thread)
{
    OsMutex *mutex;

    if (thread->mutexQueue.head == 0) {
        return;
    }

    do {
        mutex = Os_MutexQueue_Pop(&thread->mutexQueue);
        mutex->lockCount = 0;
        mutex->owner = 0;
        Os_Thread_WakeUp(&mutex->waitingThreads);
    } while (thread->mutexQueue.head != 0);
}
