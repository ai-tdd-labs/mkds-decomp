// PURPOSE: Checks whether the sound command register is available.
// Returns immediately while running in an emulator.
// On hardware, it safely probes the command register with interrupts disabled.

extern int Os_IsEmulator(void);
extern int Os_DisableIrq(void);
extern void Os_RestoreIrq(int state);

int Sound_IsCommandAvailable(void)
{
    int irqState;
    int command;

    if (Os_IsEmulator() == 0) {
        return 1;
    }

    irqState = Os_DisableIrq();
    *(volatile int *)0x04FFF200 = 0x10;
    command = *(volatile int *)0x04FFF200;
    Os_RestoreIrq(irqState);

    return command != 0;
}
