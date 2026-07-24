// PURPOSE: Finishes a pending graphics transfer and clears its saved state.
// This waits for an active DMA channel before restoring the saved configuration.
// It then clears the configuration and related state values for the next transfer.

extern int data_0216f074;
extern int data_021802ec;
extern int data_021802fc;
extern int data_02180300;
extern int data_02180304;

extern void MI_WaitDma(int dmaNo);
extern void func_021495e4(int value);

void func_0214c4d4(void)
{
    if (data_0216f074 != -1) {
        MI_WaitDma(data_0216f074);
    }

    func_021495e4(data_021802fc);
    data_02180304 = 0;
    data_02180300 = 0;
    data_021802ec = 0;
    data_021802fc = 0;
}
