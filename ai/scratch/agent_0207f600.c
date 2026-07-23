// PURPOSE: Checks whether a driver's special racer flags are clear.
// Takes a driver index and looks up that driver's entry.
// Probably reports whether none of the selected racer flags are enabled.

extern void *GetDriverEntry(int index);

int GetSomeMQRacerAnotherFlags(int index) {
    return (*(unsigned int *)((char *)GetDriverEntry(index) + 0x7c) & 0x00402020) == 0;
}
