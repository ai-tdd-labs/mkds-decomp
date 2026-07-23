// PURPOSE: Releases VRAM slots owned by a given key.
typedef unsigned int u32;

extern u32 data_02170284;
extern unsigned short data_02170288[];
extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 state);
extern int Os_CountLeadingZeroBits(u32 value);

void Os_UnlockVram(u32 mask, u32 owner)
{
    u32 slots;
    u32 irqState;
    u32 one;
    u32 zero;
    int bit;

    irqState = Os_DisableIrq();
    slots = mask & data_02170284;
    slots &= 0x1ff;
    one = 1;
    zero = 0;

    while (1) {
        bit = 31 - Os_CountLeadingZeroBits(slots);
        if (bit < 0) {
            break;
        }

        slots &= ~(one << bit);
        if (owner == data_02170288[bit]) {
            data_02170288[bit] = zero;
            data_02170284 &= ~(one << bit);
        }
    }

    Os_RestoreIrq(irqState);
}
