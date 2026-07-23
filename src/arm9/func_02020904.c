// PURPOSE: Sends a sound command using the supplied value.
// The argument is probably forwarded as the command's data value.
// The remaining command fields are cleared before sending.

extern void MaybeSoundSendCommand(int command, void *value, int arg2, int arg3,
                                  int arg4);

void func_02020904(void *value)
{
    MaybeSoundSendCommand(0x18, value, 0, 0, 0);
}
