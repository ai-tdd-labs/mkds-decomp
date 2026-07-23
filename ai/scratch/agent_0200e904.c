// PURPOSE: Receives the next queued message, optionally waiting for one.

typedef unsigned int u32;

typedef struct {
    void *head;
    void *tail;
} OsThreadQueue;

typedef struct {
    OsThreadQueue sendQueue;
    OsThreadQueue receiveQueue;
    void **messages;
    int messageCount;
    int firstMessage;
    int usedCount;
} OsMessageQueue;

extern u32 Os_DisableIrq(void);
extern u32 Os_RestoreIrq(u32 state);
extern void Os_Thread_Sleep(void *queue);

int func_0200e904(OsMessageQueue *queue, void **message, int flags)
{
    u32 irqState;

    irqState = Os_DisableIrq();
    while (queue->usedCount == 0) {
        if (!(flags & 1)) {
            Os_RestoreIrq(irqState);
            return 0;
        }
        Os_Thread_Sleep(&queue->receiveQueue);
    }

    if (message != 0) {
        *message = queue->messages[queue->firstMessage];
    }

    Os_RestoreIrq(irqState);
    return 1;
}
