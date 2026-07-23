// PURPOSE: Waits for a DMA channel to finish safely.
// The argument selects the DMA channel to poll.
// Channel zero is reset to its idle transfer state after it finishes.
// Interrupts remain disabled while the DMA registers are changed.

typedef unsigned int u32;

extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 state);

void MI_WaitDma(u32 dmaNo)
{
    u32 irqState;

    irqState = Os_DisableIrq();

    while ((*(volatile u32 *)(0x040000B0 + (dmaNo * 3 + 2) * 4) & 0x80000000) != 0) {
    }

    if (dmaNo == 0) {
        *(volatile u32 *)(0x04000000 + dmaNo * 12 + 0xB0) = 0;
        *(volatile u32 *)(0x040000B0 + dmaNo * 12 + 4) = 0;
        *(volatile u32 *)(0x040000B0 + dmaNo * 12 + 8) = 0x81400000;
    }

    Os_RestoreIrq(irqState);
}
