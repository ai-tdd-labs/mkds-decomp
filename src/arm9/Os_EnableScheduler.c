// PURPOSE: Enables scheduler activity and returns its previous disable count.
// Takes no arguments and temporarily disables interrupts while changing the count.
// The count probably tracks nested scheduler-disable requests.

typedef unsigned int u32;

extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 irqState);
extern int data_0216ff48;

int Os_EnableScheduler(void)
{
    u32 irqState = Os_DisableIrq();
    int previousCount = 0;

    if (data_0216ff48 != 0) {
        previousCount = data_0216ff48;
        data_0216ff48--;
    }

    Os_RestoreIrq(irqState);
    return previousCount;
}
