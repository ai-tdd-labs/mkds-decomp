// PURPOSE: Finishes loading the background extended palette.
// Waits for the active palette DMA transfer before restoring the bank state.
// The three saved palette state values are then cleared for the next load.

typedef signed int s32;

extern int data_0216f074;
extern int data_021802e0;
extern int data_021802dc;
extern int data_021802d8;

extern void MI_WaitDma(int dma_no);
extern void func_021498a0(s32 bgextpltt);

void func_0214b63c(void)
{
    int dmaNo = data_0216f074;

    if (dmaNo != -1) {
        MI_WaitDma(dmaNo);
    }

    func_021498a0(data_021802e0);
    data_021802dc = 0;
    data_021802d8 = 0;
    data_021802e0 = 0;
}
