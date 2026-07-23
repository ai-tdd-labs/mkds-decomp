// PURPOSE: Counts timer ticks and resets the timer hardware when requested.
// Timer IRQ handler: adds 1 to the 64-bit tick counter (data_02170254).
// If the reset flag (data_02170250) is set, it stops timer 0, clears its
// reload, restarts it with control 0xc1, and clears the flag. Then it
// re-registers itself as the timer IRQ handler.

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned long long u64;

extern volatile u64 data_02170254;
extern u32 data_02170250;
extern void Os_SetTimerIrqHandler(u32 timer, u32 callback, u32 argument);

void Os_CountTicks(void)
{
    data_02170254 += 1; // volatile u64: full read, then add, then write

    if (data_02170250 != 0) {
        *(volatile u16 *)0x04000102 = 0;    // TM0CNT_H: stop timer
        *(volatile u16 *)0x04000100 = 0;    // TM0CNT_L: reload = 0
        *(volatile u16 *)0x04000102 = 0xc1; // restart: enable + IRQ
        data_02170250 = 0;
    }

    Os_SetTimerIrqHandler(0, (u32)Os_CountTicks, 0);
}
