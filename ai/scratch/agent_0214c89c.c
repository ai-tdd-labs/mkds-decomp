typedef unsigned int u32;
typedef unsigned short u16;

extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 state);

void Mem_DmaStop(int channel)
{
    // PURPOSE: Stops and resets DMA channel zero while preserving the interrupt state.
    u32 state = Os_DisableIrq();

    *(volatile u16 *)(0x04000000 + ((channel * 6 + 5) << 1)) &= ~0x3a00;
    *(volatile u16 *)(0x04000000 + ((channel * 6 + 5) << 1)) &= ~0x8000;
    (void)*(volatile u16 *)(0x04000000 + ((channel * 6 + 5) << 1));
    (void)*(volatile u16 *)(0x04000000 + ((channel * 6 + 5) << 1));

    if (channel == 0) {
        int offset = channel * 12;

        *(volatile u32 *)(0x04000000 + offset + 0xb0) = 0;
        *(volatile u32 *)(0x040000b0 + offset + 4) = 0;
        *(volatile u32 *)(0x040000b0 + offset + 8) = 0x81400001;
    }

    Os_RestoreIrq(state);
}
