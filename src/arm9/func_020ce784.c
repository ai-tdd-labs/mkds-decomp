// PURPOSE: Checks whether the boot indicator is set to two.
// Takes no arguments and reads the system boot indicator.
// Returns one only for the probably DWC-compatible boot state.

extern unsigned short *GetBootIndicatorPointer_2(void);

int func_020ce784(void) {
    return *GetBootIndicatorPointer_2() == 2;
}
