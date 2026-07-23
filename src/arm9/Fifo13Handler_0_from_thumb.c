// PURPOSE: Handles the reset command received on FIFO channel 13.
// The first argument is unused by this handler.
// Command 1 sets the shared reset flag; other commands terminate the OS.

extern void Os_Terminate(void);
extern unsigned short data_0216fe04;

void Fifo13Handler_0_from_thumb(int unused, int command)
{
    if ((command & 0x3f) == 1) {
        data_0216fe04 = 1;
    } else {
        Os_Terminate();
    }
}
