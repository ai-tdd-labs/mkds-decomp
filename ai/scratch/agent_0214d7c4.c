// PURPOSE: Registers or removes a FIFO message handler for a channel.
// The channel number selects a handler slot and its readiness bit.
// Updates are protected while interrupts are disabled.

typedef unsigned int u32;
typedef void (*FifoHandler)(u32, u32, void *);

extern FifoHandler data_0218032c[];
extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 state);

void Fifo_RegisterHandler(int channel, FifoHandler handler)
{
    u32 state;

    state = Os_DisableIrq();
    data_0218032c[channel] = handler;
    if (handler != 0) {
        *(volatile u32 *)(0x027ffc00 + 0x388) |= 1 << channel;
    } else {
        *(volatile u32 *)(0x027ffc00 + 0x388) &= ~(1 << channel);
    }
    Os_RestoreIrq(state);
}
