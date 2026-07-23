typedef unsigned int u32;

typedef struct OsThread OsThread;

typedef struct {
    OsThread *head;
    OsThread *tail;
} OsThreadQueue;

typedef struct {
    int *result;
    int command;
    volatile int owner;
    volatile int lockCount;
    OsThreadQueue waitingThreads;
    int resource;
} CardResource;

extern CardResource data_0217fa40;

extern u32 Os_DisableIrq(void);
extern u32 Os_RestoreIrq(u32 irqState);
extern void Os_Terminate(void);
extern void Os_Thread_Sleep(OsThreadQueue *queue);

void Card_LockResource(int owner, int resource)
{
    // PURPOSE: Acquires exclusive ownership of a shared card resource.
    CardResource *state = &data_0217fa40;
    u32 irqState = Os_DisableIrq();

    if (state->owner == owner) {
        if (state->resource != resource) {
            Os_Terminate();
        }
    } else {
        if (state->owner != -3) {
            do {
                Os_Thread_Sleep(&state->waitingThreads);
            } while (state->owner != -3);
        }
        state->owner = owner;
        state->resource = resource;
    }
    state->lockCount++;
    *state->result = 0;
    (void)Os_RestoreIrq(irqState);
}
