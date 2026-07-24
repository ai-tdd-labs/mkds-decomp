// PURPOSE: Finishes loading the main-screen background palette.
// Waits for the active DMA transfer, probably restores the saved palette bank,
// and clears the saved state for the next load.

extern int data_0216f074;
extern int data_021802e8;
extern int data_021802f8;

extern void MI_WaitDma(int dma_no);
extern void func_021493b0(int bank);

void func_0214c1bc(void)
{
    if (data_0216f074 != -1) {
        MI_WaitDma(data_0216f074);
    }

    func_021493b0(data_021802e8);
    data_021802e8 = 0;
    data_021802f8 = 0;
}
