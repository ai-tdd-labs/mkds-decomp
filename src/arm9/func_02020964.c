// PURPOSE: Sends sound command 23 with the supplied value.
// The input is forwarded as the second command argument.
// The remaining command arguments are probably unused and are cleared.

extern void MaybeSoundSendCommand(int command, int value, int arg2, int arg3,
                                  int arg4);

void func_02020964(int value)
{
    MaybeSoundSendCommand(0x17, value, 0, 0, 0);
}
