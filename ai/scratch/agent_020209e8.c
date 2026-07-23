// PURPOSE: Sends a sound command with two supplied values.
/*
 * The two arguments are probably sound-command parameters.
 * This wrapper selects command 30 and clears the remaining fields.
 */

extern void MaybeSoundSendCommand(int command, int value0, int value1,
                                  int value2, int value3);

void func_020209e8(int value0, int value1)
{
    MaybeSoundSendCommand(30, value0, value1, 0, 0);
}
