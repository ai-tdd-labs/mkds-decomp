// PURPOSE: Locks a sound channel for use.
// Sends the channel parameters through the sound command dispatcher.
// The final command argument is probably a reserved value and is zero here.

extern void MaybeSoundSendCommand(int command, int channel, int value,
                                  int flags, int reserved);

void SND_LockChannel(int channel, int value)
{
    MaybeSoundSendCommand(0x1A, channel, value, 0, 0);
}
