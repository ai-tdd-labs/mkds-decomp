// PURPOSE: Sends a sound command with a fixed command type.
// Passes four caller values to the sound-command dispatcher.
// The leading command value is always 2.

extern void MaybeSoundSendCommand(int command, int arg0, int arg1, int arg2, int arg3);

void func_02020ddc(int arg0, int arg1, int arg2, int arg3)
{
    MaybeSoundSendCommand(2, arg0, arg1, arg2, arg3);
}
