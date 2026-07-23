// PURPOSE: Initializes the wireless manager state.
// Takes the manager work pointer and DMA channel from its caller.
// Probably clears the manager's status field after successful setup.

extern int Wm_InitializeImpl(void *work, unsigned int dma_channel, unsigned int size);
extern unsigned char *data_0217eed4;

int Wm_Initialize(void *work, unsigned int dma_channel) {
    if (Wm_InitializeImpl(work, dma_channel, 0xf00) == 0) {
        *(unsigned short *)(data_0217eed4 + 0x16) = 0;
    }
}
