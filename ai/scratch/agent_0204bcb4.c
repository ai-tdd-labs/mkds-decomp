// PURPOSE: Updates the system callback pointer safely.
// The argument supplies a pointer whose low flag bit is discarded.
// This probably records the pointer while interrupts are disabled.

typedef unsigned int u32;

extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 irqState);
extern char data_02179ec0[];

void func_0204bcb4(void *value)
{
    u32 irqState = Os_DisableIrq();

    *(void **)(data_02179ec0 + 0xb10) = (void *)((u32)value & ~1);
    Os_RestoreIrq(irqState);
}
