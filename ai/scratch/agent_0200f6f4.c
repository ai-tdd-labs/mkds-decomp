/* PURPOSE: Turns on the system tick clock the game uses to measure time.
 * Takes no arguments and returns nothing. Runs only once: if the tick
 * system is already marked initialized it returns immediately.
 * It reserves hardware timer 0, zeroes the 64-bit tick counter, resets
 * the timer-0 MMIO registers, starts the timer (control 0xc1, probably
 * enable + IRQ + prescaler), installs Os_CountTicks as the timer-0
 * interrupt handler, enables that IRQ, and clears a probably
 * "tick needs reset" flag.
 */

typedef unsigned short u16;
typedef unsigned int u32;

typedef struct TickCounter {
    u32 lo;
    u32 hi;
} TickCounter;

extern u16 data_0217024c;          /* tick-initialized flag */
extern u32 data_02170250;          /* probably tick-reset flag */
extern volatile TickCounter data_02170254;  /* 64-bit tick counter */

extern u32 Os_ReserveTimer(u32 timer);
extern void Os_CountTicks(void);
extern void Os_SetIrqHandler(u32 mask, void (*handler)(void));
extern u32 Os_EnableIrqHandler(u32 mask);

void Os_InitializeTick(void)
{
    if (data_0217024c != 0) {
        return;
    }

    data_0217024c = 1;
    Os_ReserveTimer(0); /* reserve hardware timer 0 */

    data_02170254.lo = 0;
    data_02170254.hi = 0;

    /* Timer-0 MMIO: stop control, clear reload, then start with 0xc1. */
    *(volatile u16 *)0x04000102 = 0;
    *(volatile u16 *)0x04000100 = 0;
    *(volatile u16 *)0x04000102 = 0xc1;

    Os_SetIrqHandler(8, Os_CountTicks);
    Os_EnableIrqHandler(8);

    data_02170250 = 0;
}
