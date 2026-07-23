// PURPOSE: Stores a pointer in shared system state.
// The pointer is supplied by the caller.
// This probably updates a system field while interrupts are disabled.

typedef unsigned int u32;

extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 irqState);
extern char *data_0216fde8;

void func_0200ba84(void *value)
{
    u32 irqState = Os_DisableIrq();

    *(void **)(data_0216fde8 + 0x5e0) = value;
    Os_RestoreIrq(irqState);
}
