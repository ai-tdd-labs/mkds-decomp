// PURPOSE: Starts the wireless FIFO setup when it has not already started.
// The routine records the setup state and terminates if the FIFO setup fails.
// It probably waits here while the shared wireless state reports value two.

extern int data_02175614;
extern volatile int func_02039abc;

extern int SetWvrFifoShit(void *a0, int a1, int *a2, int a3);
extern void Os_Terminate(void);

void MaybeInitializeSomeWirelessShit(void)
{
    if (data_02175614 == 1) {
        goto wait;
    }
    if (data_02175614 == 3) {
        goto wait;
    }

    data_02175614 = 2;
    if (SetWvrFifoShit(&func_02039abc, 1, &data_02175614, 2) != 1) {
        Os_Terminate();
    }

wait:
    for (;;) {
        int waiting = 1;

        if (func_02039abc != 2) {
            waiting = 0;
        }
        if (waiting == 0) {
            break;
        }
    }
}
