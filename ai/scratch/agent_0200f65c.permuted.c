// PURPOSE: Counts timer ticks and resets the timer hardware when requested.
// The count is kept as a 64-bit value in shared state.
// A nonzero reset flag clears the timer registers before the IRQ callback is set.

typedef unsigned int u32;
typedef unsigned short u16;

extern unsigned long long data_02170254;
extern u32 data_02170250;
extern void Os_SetTimerIrqHandler(u32 timer, u32 callback, u32 argument);

void Os_CountTicks(void)
{
    data_02170254++;

    if (data_02170250 != 0) {
        *(volatile u16 *)0x04000102 = 0;
        *(volatile u16 *)0x04000100 = 0;
        *(volatile u16 *)0x04000102 = 0xc1;
        data_02170250 = 0;
    }

    Os_SetTimerIrqHandler(0, (u32)Os_CountTicks, 0);
}
