// PURPOSE: Resets the display configuration to its default state.
// This function takes no arguments.
// It probably clears the current display configuration after resetting VRAM.

extern void ResetSomeVram(void);
extern int data_021755a0;

void ResetDisplayConfig(void) {
    ResetSomeVram();
    data_021755a0 = 0;
}
