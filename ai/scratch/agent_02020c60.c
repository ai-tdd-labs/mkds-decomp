// PURPOSE: Sends sound command nine with three values.
// The values are forwarded as the first three command parameters.
// The final command parameter is cleared.

typedef unsigned int u32;
typedef int s32;

extern void MaybeSoundSendCommand(s32 command, u32 parameter1, u32 parameter2,
                                  u32 parameter3, u32 parameter4);

void func_02020c60(u32 parameter1, u32 parameter2, u32 parameter3)
{
    MaybeSoundSendCommand(9, parameter1, parameter2, parameter3, 0);
}
