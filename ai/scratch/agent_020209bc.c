// PURPOSE: Sends a sound command with two parameters.
/*
 * The two inputs are forwarded as the command's first two parameters.
 * The remaining parameters are cleared, probably selecting a default action.
 */

typedef unsigned int u32;
typedef int s32;

extern void MaybeSoundSendCommand(s32 command, u32 parameter1, u32 parameter2,
                                  u32 parameter3, u32 parameter4);

void func_020209bc(u32 parameter1, u32 parameter2)
{
    MaybeSoundSendCommand(0x1f, parameter1, parameter2, 0, 0);
}
