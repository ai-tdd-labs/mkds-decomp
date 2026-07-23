// PURPOSE: Sends a sound command with four parameters.
// The parameters are forwarded unchanged to the sound command handler.
// Command 6 probably selects this particular sound operation.

typedef unsigned int u32;

extern void MaybeSoundSendCommand(int command, u32 parameter1, u32 parameter2,
                                  u32 parameter3, u32 parameter4);

void func_020208a4(u32 parameter1, u32 parameter2, u32 parameter3,
                   u32 parameter4)
{
    MaybeSoundSendCommand(6, parameter1, parameter2, parameter3, parameter4);
}
