// PURPOSE: Receives the next message from a message queue.
// The queue, optional output pointer, and wait flags are supplied by the caller.
// It returns zero when an empty queue may not block, otherwise it waits for a message.
// Interrupts remain disabled while the queue state is changed.

typedef unsigned int u32;

typedef struct {
    void *head;
    void *tail;
} OsThreadQueue;

typedef struct {
    OsThreadQueue sendQueue;    /* 0x00 */
    OsThreadQueue receiveQueue; /* 0x08 */
    void **messages;            /* 0x10 */
    int messageCount;           /* 0x14 */
    int firstMessage;           /* 0x18 */
    int usedCount;              /* 0x1c */
} OsMessageQueue;

extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 state);
extern void Os_Thread_Sleep(void *queue);
extern void Os_Thread_WakeUp(void *queue);
extern long long _s32_div_f(int dividend, int divisor);

int Os_ReceiveMessage(OsMessageQueue *queue, void **message, int flags)
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
    queue->firstMessage = (int)(_s32_div_f(queue->firstMessage + 1, queue->messageCount) >> 32);
    queue->usedCount--;
    Os_Thread_WakeUp(queue);
    Os_RestoreIrq(irqState);
    return 1;
}
