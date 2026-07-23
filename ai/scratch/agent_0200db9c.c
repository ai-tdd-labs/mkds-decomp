// PURPOSE: Temporarily disables the scheduler and returns its previous state.
// This function disables interrupts while updating the scheduler state.
// The exact scheduler-state meaning is probably an internal nesting counter.

typedef unsigned int u32;

extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 irqState);
extern u32 data_0216ff48;

u32 Os_DisableScheduler(void)
{
    u32 irqState = Os_DisableIrq();
    u32 previousState;

    if (data_0216ff48 < 0xFFFFFFFF) {
        previousState = data_0216ff48;
        data_0216ff48 = previousState + 1;
    }

    Os_RestoreIrq(irqState);
    return previousState;
}
