// PURPOSE: Sends a sound command using four supplied parameters.
// Four parameters are forwarded unchanged after the fixed command identifier.
// This probably sends one of the sound system's multi-field commands.

typedef unsigned int u32;
typedef int s32;

extern void MaybeSoundSendCommand(s32 command, u32 parameter1, u32 parameter2,
                                  u32 parameter3, u32 parameter4);

void func_02020930(u32 parameter1, u32 parameter2, u32 parameter3,
                   u32 parameter4)
{
    MaybeSoundSendCommand(0x19, parameter1, parameter2, parameter3, parameter4);
}
