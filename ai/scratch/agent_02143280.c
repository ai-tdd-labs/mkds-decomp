// PURPOSE: Reads the wireless status value.
// Takes no arguments.
// Returns the initialized-state marker or the shared wireless status.
// The shared memory value is probably maintained by the wireless subsystem.

extern int Wm_CheckInitialized(void);

int func_02143280(void) {
    if (Wm_CheckInitialized()) {
        return 0x8000;
    }

    return *(volatile unsigned short *)0x027FFCFA;
}
