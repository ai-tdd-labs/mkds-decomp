// PURPOSE: Wakes every thread waiting in a queue.
// The queue is drained while interrupts are disabled.
// Each removed thread is marked runnable before scheduling is requested.
// The exact link fields are probably internal OS bookkeeping.

typedef unsigned int u32;

typedef struct OsThread OsThread;

typedef struct OsThreadQueue {
    OsThread *head;
    OsThread *tail;
} OsThreadQueue;

struct OsThread {
    unsigned char unknown00[0x64];
    int state;
    unsigned char unknown68[0x10];
    void *queue;
    OsThread *previous;
    OsThread *next;
};

extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 irqState);
extern OsThread *Os_ThreadQueue_Pop(OsThreadQueue *queue);
extern void Os_RescheduleThread(void);

void Os_Thread_WakeUp(OsThreadQueue *queue)
{
    u32 irqState = Os_DisableIrq();

    if (queue->head != 0) {
        while (queue->head != 0) {
            OsThread *thread = Os_ThreadQueue_Pop(queue);

            thread->state = 1;
            thread->queue = 0;
            thread->next = 0;
            thread->previous = thread->next;
        }

        queue->tail = 0;
        queue->head = queue->tail;
        Os_RescheduleThread();
    }

    Os_RestoreIrq(irqState);
}
