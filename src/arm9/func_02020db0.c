// PURPOSE: Sends sound command three with a value.
// The input is passed as the command's first parameter.
// The remaining command parameters are cleared.

typedef unsigned int u32;
typedef int s32;

extern void MaybeSoundSendCommand(s32 command, u32 parameter1, u32 parameter2,
                                  u32 parameter3, u32 parameter4);

void func_02020db0(u32 value)
{
    MaybeSoundSendCommand(3, value, 0, 0, 0);
}
