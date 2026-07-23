// PURPOSE: Returns how long the system has been running, as one big tick number.
// Reads the 48-bit software tick counter plus the live hardware timer-0 count,
// with interrupts disabled so the two stay consistent. If a timer overflow is
// already pending (IF bit 3) but not yet reflected in the counter, it adds one
// missed overflow. Returns (counter << 16) | timerCount.
// Locals are volatile to force the stack spill/reload pattern of the original.

typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 irqState);
extern u64 data_02170254; // tick counter kept by the timer-0 IRQ handler

u64 Os_GetTick(void)
{
    volatile u16 count; // hardware timer-0 counter snapshot (sp+0)
    volatile u64 tick;  // masked software counter (sp+4/sp+8)
    u32 irqState;

    irqState = Os_DisableIrq();
    count = *(volatile u16 *)0x04000100;          // TM0CNT_L
    // volatile read pins the counter loads AFTER the count store (source order)
    tick = *(volatile u64 *)&data_02170254 & 0x0000ffffffffffffULL; // 48 bits wide
    // Overflow interrupt pending but counter not yet advanced: count it now.
    if ((*(volatile u32 *)0x04000214 & 8) && !(count & 0x8000)) {
        tick++;
    }
    Os_RestoreIrq(irqState);
    // count promotes through signed int, giving the asr #31 into the high word.
    return (tick << 16) | count;
}
