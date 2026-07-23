// PURPOSE: Sends the sound system reset command.
// The command has no active parameters.
// It probably clears or initializes an internal sound command state.

typedef unsigned int u32;
typedef int s32;

extern void MaybeSoundSendCommand(s32 command, u32 parameter1, u32 parameter2,
                                  u32 parameter3, u32 parameter4);

void func_020208d8(void)
{
    MaybeSoundSendCommand(0x18, (u32)-1, 0, 0, 0);
}
