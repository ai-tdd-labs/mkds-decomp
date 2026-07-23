// PURPOSE: Checks whether the boot indicator is in DWC mode.
// Takes no arguments.
// Probably accepts only boot state two.

extern unsigned short *GetBootIndicatorPointer_0(void);

int IsDwc_0(void) {
    return *GetBootIndicatorPointer_0() == 2;
}
