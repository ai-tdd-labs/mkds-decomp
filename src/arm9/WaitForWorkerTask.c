// PURPOSE: Waits until the worker task has finished.
// This takes no arguments and returns after the pending worker-task flag clears.
// It probably yields to IRQ processing while the background save worker is busy.

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct {
    u8 pad_00[0xf8];
    u32 taskPending;
} SaveWorkerState;

extern SaveWorkerState *data_0217aa0c;

extern void WaitForIRQ(int irq, int flags);

void WaitForWorkerTask(void)
{
    if (data_0217aa0c->taskPending == 0) {
        return;
    }

    do {
        WaitForIRQ(1, 1);
    } while (data_0217aa0c->taskPending != 0);
}
