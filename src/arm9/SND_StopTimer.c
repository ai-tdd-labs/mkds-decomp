/* PURPOSE: Stops the selected sound timers.
 * The masks select sound channels, capture units, and alarms to stop.
 * Each selected alarm has its generation counter advanced before the stop
 * command is sent, preventing an old alarm event from being reused.
 */

typedef unsigned int u32;
typedef int s32;

extern void IncreaseMDCounter(u32 alarm);
extern void MaybeSoundSendCommand(s32 command, u32 parameter1, u32 parameter2,
                                  u32 parameter3, u32 parameter4);

void SND_StopTimer(u32 channelMask, u32 captureMask, u32 alarmMask, u32 flags)
{
    s32 alarm = 0;
    u32 remainingAlarms = alarmMask;

    while (alarm < 8 && remainingAlarms != 0) {
        if (remainingAlarms & 1)
            IncreaseMDCounter((u32)alarm);
        alarm++;
        remainingAlarms >>= 1;
    }

    MaybeSoundSendCommand(0xd, channelMask, captureMask, alarmMask, flags);
}
