// PURPOSE: Checks whether the DWC boot indicator is active.
// Takes no arguments.
// Returns one only when the indicator has value two.
// Probably identifies the DWC-compatible boot state.

extern unsigned short *GetBootIndicatorPointer_1(void);

int IsDwc_1(void) {
    return *GetBootIndicatorPointer_1() == 2;
}
