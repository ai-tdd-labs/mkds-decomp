// PURPOSE: Starts a sound timer with the supplied settings.
// The four arguments are forwarded to the sound command dispatcher.
// Their individual meanings are probably internal timer parameters.

typedef unsigned int u32;
typedef int s32;

extern void MaybeSoundSendCommand(s32 command, u32 parameter1, u32 parameter2,
                                  u32 parameter3, u32 parameter4);

void SND_StartTimer(u32 channelMask, u32 captureMask, u32 alarmMask, u32 flags)
{
    MaybeSoundSendCommand(0xc, channelMask, captureMask, alarmMask, flags);
}
