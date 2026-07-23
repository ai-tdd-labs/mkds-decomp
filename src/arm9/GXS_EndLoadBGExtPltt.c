// PURPOSE: Finishes loading the sub-screen background palette.
// Waits for the active DMA transfer, probably restores the saved palette bank,
// and marks the DMA channel as inactive.

extern int data_0216f074;
extern int data_021802cc;

extern void MI_WaitDma(int dmaNo);
extern void GX_SetBankForSubBGExtPltt(int bank);

void GXS_EndLoadBGExtPltt(void)
{
    int dmaNo = data_0216f074;

    if (dmaNo != -1) {
        MI_WaitDma(dmaNo);
    }
    GX_SetBankForSubBGExtPltt(data_021802cc);
    data_021802cc = 0;
}
