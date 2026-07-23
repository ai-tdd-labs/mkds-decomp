// PURPOSE: Sends a sound command with three supplied values.
/*
 * The three arguments are forwarded as the command parameters.
 * This probably submits sound command 8 with a zero final parameter.
 */

extern void MaybeSoundSendCommand(int command, int value1, int value2, int value3, int value4);

void func_02020af8(int value1, int value2, int value3)
{
    MaybeSoundSendCommand(8, value1, value2, value3, 0);
}
