// PURPOSE: Handles an incoming sound FIFO command.
// The second argument is probably an alarm callback payload.
// Interrupts are disabled while the sound handler processes it.

typedef unsigned int u32;

extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 irqState);
extern void Sound_CallAlarmHandler(void *payload);

void Sound_FifoHandler(int command, void *payload)
{
    u32 irqState = Os_DisableIrq();

    /* The FIFO's payload is dispatched while IRQ state is held. */
    Sound_CallAlarmHandler(payload);
    Os_RestoreIrq(irqState);
}
