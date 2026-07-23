/* PURPOSE: Sets up a sound alarm and registers the function it will call.
 * The alarm number, start tick, and repeat period are sent to the sound system.
 * The callback and user data are stored locally, and their registration ID is
 * included in sound command 0x12 so the alarm can invoke the right handler. */

typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;
typedef void (*SNDAlarmCallback)(void *);

extern void MaybeSoundSendCommand(s32 command, u32 parameter1, u32 parameter2,
                                  u32 parameter3, u32 parameter4);
extern u8 SetMDValue(u32 alarm, SNDAlarmCallback callback, void *userData);

void func_02020b2c(s32 alarm, u32 tick, u32 period,
                   SNDAlarmCallback callback, void *userData)
{
    MaybeSoundSendCommand(0x12, (u32)alarm, tick, period,
                          SetMDValue((u32)alarm, callback, userData));
}
