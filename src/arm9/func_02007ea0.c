// PURPOSE: Stores a shared pointer while interrupts are disabled.
// The argument is probably recorded in a global manager structure.
// Interrupt state is restored immediately after the pointer write.

typedef unsigned int u32;

extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 irqState);
extern char *data_0216fdac;

void func_02007ea0(void *pointer)
{
    u32 irqState = Os_DisableIrq();

    *(void **)(data_0216fdac + 0x14e4) = pointer;
    Os_RestoreIrq(irqState);
}
