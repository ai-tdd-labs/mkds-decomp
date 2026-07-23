// PURPOSE: Sends a simple sound command with two parameters.
// The two inputs are forwarded as the command's first two parameters.
// The remaining sound parameters are cleared, probably for a basic control request.

typedef unsigned int u32;
typedef int s32;

extern void MaybeSoundSendCommand(s32 command, u32 parameter1, u32 parameter2,
                                  u32 parameter3, u32 parameter4);

void func_02020990(u32 parameter1, u32 parameter2)
{
    MaybeSoundSendCommand(0x20, parameter1, parameter2, 0, 0);
}
