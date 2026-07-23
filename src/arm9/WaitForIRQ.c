// PURPOSE: Pauses the game code until a chosen hardware interrupt has happened.
// arg0 (clear): when nonzero, first clears the requested interrupt-seen bits
//   so only a NEW interrupt can wake the caller.
// arg1 (mask): which interrupt bits to wait for.
// Behaviour: with interrupts disabled it optionally clears the bits in the
// IRQ check flag (DTCM base + 0x3ff8), re-enables interrupts, and if the bits
// are not already set it sleeps on the IRQ thread queue (start of DTCM) until
// an interrupt handler sets one of the requested bits.

typedef unsigned int u32;
typedef unsigned char u8;

extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 irqState);
extern void Os_Thread_Sleep(void *queue);

// Start of DTCM; the interrupt check flag word sits at +0x3ff8
// (mirrors HW_INTR_CHECK_BUF).
extern u8 data_027e0000[];

void WaitForIRQ(int clear, u32 mask)
{
    u32 irqState;

    irqState = Os_DisableIrq();
    if (clear) {
        // read-modify-write of the check flag with interrupts off
        // int cursor advanced in place so the base register is reused
        int a = (int)data_027e0000;
        a += 0x3000;
        *(volatile u32 *)(a + 0xff8) &= ~mask;
    }
    Os_RestoreIrq(irqState);

    if (!(mask & ((volatile u32 *)((int)data_027e0000 + 0x3000))[0x3fe])) {
        // different spelling of the same address so the compiler keeps
        // this pointer computation after the early-return branch
        volatile u32 *check = (volatile u32 *)((int)data_027e0000 + 0x3ff8);
        do {
            // sleep on the IRQ thread queue at the start of DTCM
            Os_Thread_Sleep((void *)0x027e0000);
        } while (!(mask & *check));
    }
}
