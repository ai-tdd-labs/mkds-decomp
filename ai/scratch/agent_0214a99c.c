// PURPOSE: Clears the 3D graphics command FIFO before continuing.
// Arguments: none.
// It probably waits until the graphics FIFO is no longer busy.
// The command port and status register are fixed hardware addresses.

extern void GXi_NopClearFifo128_(void *);

void G3X_ClearFifo(void) {
    GXi_NopClearFifo128_((void *)0x04000400);
    while (*(volatile unsigned int *)0x04000600 & 0x08000000) {
    }
}
