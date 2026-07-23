// PURPOSE: Waits for a pending card operation to finish.
// The shared card state probably owns the operation result and wait queue.
// It sleeps with interrupts disabled until the pending-operation flag is clear.

typedef unsigned int u32;

typedef struct CardCommandState {
    void *result;
    char padding_04[0x108];
    int sleepQueue;
    char padding_110[4];
    u32 flags;
} CardCommandState;

extern CardCommandState data_0217fa40;

extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 state);
extern void Os_Thread_Sleep(void *queue);

int WaitForPendingCardOperation(void)
{
    u32 irqState;

    irqState = Os_DisableIrq();
    while ((data_0217fa40.flags & 4) != 0) {
        Os_Thread_Sleep(&data_0217fa40.sleepQueue);
    }
    Os_RestoreIrq(irqState);
    return (*(int *)data_0217fa40.result == 0);
}
