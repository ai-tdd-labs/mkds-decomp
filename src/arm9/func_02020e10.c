// PURPOSE: Sends a simple sound command with the supplied value.
// The value is passed as the command's first parameter.
// The remaining command parameters are probably unused here.

typedef int s32;
typedef unsigned int u32;

extern void MaybeSoundSendCommand(s32 command, u32 parameter1, u32 parameter2,
                                  u32 parameter3, u32 parameter4);

void func_02020e10(u32 value)
{
    MaybeSoundSendCommand(1, value, 0, 0, 0);
}
