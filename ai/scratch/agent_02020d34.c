// PURPOSE: Sends a sound command with three supplied values.
// The three arguments are forwarded to sound command 10.
// The final command value is probably an unused zero parameter.

extern void MaybeSoundSendCommand(int command, int value0, int value1,
                                  int value2, int value3);

void func_02020d34(int value0, int value1, int value2)
{
    MaybeSoundSendCommand(10, value0, value1, value2, 0);
}
