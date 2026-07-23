// PURPOSE: Prepares video memory for the selected display mode.
/* Chooses an LCDC bank arrangement from the current mode value.
 * The selected VRAM ranges are cleared before LCDC access is disabled.
 * Mode values outside the known range only disable LCDC access.
 */

extern int data_02175614;

extern void GX_SetBankForLCDC(int bank);
extern void GX_DisableBankForLCDC(void);
extern void Mem_CpuFastMemorySet(int value, void *dst, int size);

void MaybePrepareVram(void)
{
    volatile int zero0;
    volatile int zero1;
    volatile int zero2;

    switch (data_02175614) {
    case 0:
        GX_SetBankForLCDC(0x1f7);
        Mem_CpuFastMemorySet(zero0 = 0, (void *)0x06800000, 0x60000);
        Mem_CpuFastMemorySet(zero1 = 0, (void *)0x06880000, 0x24000);
        break;
    case 1:
    case 3:
        GX_SetBankForLCDC(0x1ff);
        Mem_CpuFastMemorySet(zero2 = 0, (void *)0x06800000, 0xa4000);
        break;
    case 2:
        break;
    }
    GX_DisableBankForLCDC();
}
