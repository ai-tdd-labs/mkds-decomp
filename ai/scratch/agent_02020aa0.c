// PURPOSE: Releases a sound channel for use.
// The channel and its parameter are sent to the sound command handler.
// The remaining command fields are cleared.

typedef unsigned int u32;
typedef int s32;

extern void MaybeSoundSendCommand(s32 command, u32 parameter1, u32 parameter2,
                                  u32 parameter3, u32 parameter4);

void SND_UnlockChannel(u32 channel, u32 parameter)
{
    MaybeSoundSendCommand(0x1b, channel, parameter, 0, 0);
}
