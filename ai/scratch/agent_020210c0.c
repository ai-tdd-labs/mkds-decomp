// PURPOSE: Checks whether a tick time has been reached.
// The comparison is protected from interrupt updates to the current tick.
// It handles the unsigned timer wraparound boundary.

typedef unsigned int u32;

extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 irqState);
extern u32 data_021732cc;

int func_020210c0(u32 tick)
{
    u32 irqState;
    int available;

    irqState = Os_DisableIrq();
    if (tick > data_021732cc) {
        if (tick - data_021732cc < 0x80000000) {
            available = 0;
        } else {
            available = 1;
        }
    } else {
        if (data_021732cc - tick < 0x80000000) {
            available = 1;
        } else {
            available = 0;
        }
    }
    Os_RestoreIrq(irqState);
    return available;
}
