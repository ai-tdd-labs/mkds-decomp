/*
PURPOSE: Marks the system ready after a valid reset message.
The callback receives a FIFO tag, message data, and an error flag; only the
message data is used here. A reset command sets the reset-ready flag, while
any other command terminates the system.
*/

extern void Os_Terminate(void);
extern unsigned short data_02170280;

void Os_FifoResetHandler(int tag, int data, int error)
{
    if ((unsigned int)((data & 0x7f00) << 8) >> 16 == 0x10) {
        data_02170280 = 1;
        return;
    }

    Os_Terminate();
}
