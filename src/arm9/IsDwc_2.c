// PURPOSE: Checks whether the BIOS boot indicator has value two.
// Takes no arguments.
// Probably identifies the DWC-compatible boot state.
extern unsigned short *GetBiosBootIndicatorRef(void);

int IsDwc_2(void) {
    return *GetBiosBootIndicatorRef() == 2;
}
