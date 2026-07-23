// PURPOSE: Inserts a message at the front of a queue, ahead of waiting messages.

typedef unsigned int u32;

typedef struct OsThread OsThread;

typedef struct {
    OsThread *head;
    OsThread *tail;
} OsThreadQueue;

typedef struct {
    OsThreadQueue sendQueue;
    OsThreadQueue receiveQueue;
    void **messages;
    int capacity;
    int first;
    int count;
} OsMessageQueue;

extern u32 Os_DisableIrq(void);
extern u32 Os_RestoreIrq(u32 state);
extern void Os_Thread_Sleep(OsMessageQueue *queue);
extern void Os_Thread_WakeUp(OsThreadQueue *queue);

int OS_JamMessage(OsMessageQueue *queue, void *message, int flags)
{
    u32 irqState;

    irqState = Os_DisableIrq();

    while (queue->capacity <= queue->count) {
        if ((flags & 1) == 0) {
            (void)Os_RestoreIrq(irqState);
            return 0;
        }
        Os_Thread_Sleep(queue);
    }

    queue->first = (queue->first + queue->capacity - 1) % queue->capacity;
    queue->messages[queue->first] = message;
    queue->count++;
    Os_Thread_WakeUp(&queue->receiveQueue);
    (void)Os_RestoreIrq(irqState);
    return 1;
}
