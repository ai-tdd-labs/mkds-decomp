// PURPOSE: Finishes loading the object extended palette.
// Waits for the pending palette DMA transfer, probably restores the selected
// palette bank, and clears the saved state for the next load.

extern int data_0216f074;
extern int data_021802d4;
extern int data_021802d0;

extern void MI_WaitDma(int dma_no);
extern void GX_SetBankForOBJExtPltt(int bank);

void GX_EndLoadOBJExtPltt(void)
{
    if (data_0216f074 != -1) {
        MI_WaitDma(data_0216f074);
    }

    GX_SetBankForOBJExtPltt(data_021802d4);
    data_021802d4 = 0;
    data_021802d0 = 0;
}
