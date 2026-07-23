// PURPOSE: Finishes loading the sub screen object palette.
// The pending DMA channel is probably waited on before changing the palette bank.
// The selected bank is applied and then cleared for the next load.

extern int data_0216f074;
extern int data_021802e4;

extern void MI_WaitDma(int dma_no);
extern void GX_SetBankForSubOBJExtPltt(int bank);

void GXS_EndLoadOBJExtPltt(void)
{
    if (data_0216f074 != -1) {
        MI_WaitDma(data_0216f074);
    }

    GX_SetBankForSubOBJExtPltt(data_021802e4);
    data_021802e4 = 0;
}
