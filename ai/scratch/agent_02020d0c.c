// PURPOSE: Sends a sound command with three supplied values.
// The first two values are passed through unchanged.
// The third value is probably a sound-command parameter.
// This wrapper supplies fixed values for the remaining parameters.

typedef int s32;
typedef unsigned int u32;

extern void MaybeSoundSendCommand(s32 command, u32 parameter1, u32 parameter2,
                                  u32 parameter3, u32 parameter4);

void func_02020d0c(s32 command, u32 parameter1, u32 parameter3)
{
    MaybeSoundSendCommand(command, parameter1, 10, parameter3, 2);
}
