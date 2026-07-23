// PURPOSE: Sets the volume of a sound channel.
/*
 * Sends the channel and volume parameters to the sound command handler.
 * The third parameter is probably an additional channel-volume setting.
 */

extern void MaybeSoundSendCommand(int command, int channel, int volume,
                                  int parameter, int unused);

void SND_SetChannelVolume(int channel, int volume, int parameter)
{
    MaybeSoundSendCommand(0x14, channel, volume, parameter, 0);
}
