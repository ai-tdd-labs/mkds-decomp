// PURPOSE: Marks the shared system state as active.
// This function disables interrupts while checking and setting a global flag.
// It returns whether the flag was previously clear.
// The flag probably prevents the state from being activated twice.

extern unsigned int Os_DisableIrq(void);
extern void Os_RestoreIrq(unsigned int state);
extern int data_02180448;

int func_021501d8(void) {
    unsigned int state = Os_DisableIrq();

    if (data_02180448 != 0) {
        Os_RestoreIrq(state);
        return 0;
    }

    data_02180448 = 1;
    Os_RestoreIrq(state);
    return 1;
}
