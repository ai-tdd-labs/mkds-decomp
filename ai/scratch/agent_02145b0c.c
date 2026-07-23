// PURPOSE: Queues a card task and wakes the card worker thread.

typedef unsigned int u32;

typedef struct OsThread OsThread;

typedef struct CardContext {
    unsigned char pad_000[0x40];
    void (*task)(struct CardContext *context);
    unsigned char thread[0xc0];
    OsThread *currentThread;
    int threadPriority;
    unsigned char pad_10c[8];
    volatile u32 status;
} CardContext;

extern CardContext data_0217fa40;

extern int Os_Thread_SetPriority(OsThread *thread, int priority);
extern void Os_Thread_WakeUpDirect(void *thread);

void Card_SetTask(void (*task)(CardContext *context))
{
    CardContext *context = &data_0217fa40;

    Os_Thread_SetPriority((OsThread *)task, context->threadPriority);
    context->currentThread = (OsThread *)context->thread;
    context->task = task;
    context->status |= 8;
    Os_Thread_WakeUpDirect(context->thread);
}
