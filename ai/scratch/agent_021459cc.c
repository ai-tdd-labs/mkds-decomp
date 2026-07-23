// PURPOSE: Releases a card resource held by its current owner.
// The first argument identifies the owner and the second selects the card resource.
// It validates the lock, releases its final reference, and wakes waiting threads.

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
extern void Os_Thread_WakeUp(OsThreadQueue *queue);

void Card_UnlockResource(int owner, int resource)
{
    CardResource *state = &data_0217fa40;
    u32 irqState = Os_DisableIrq();

    if (state->owner != owner || state->lockCount == 0) {
        Os_Terminate();
    } else {
        if (state->resource != resource) {
            Os_Terminate();
        }
        if (--state->lockCount == 0) {
            state->owner = -3;
            state->resource = 0;
            Os_Thread_WakeUp(&state->waitingThreads);
        }
    }
    *state->result = 0;
    (void)Os_RestoreIrq(irqState);
}
