// PURPOSE: Sends a packed sound command to the sound system.
// The caller supplies several bit-field values that are combined into four command words.
// The ninth input is probably reserved because this wrapper does not use it.

typedef unsigned int u32;

extern void MaybeSoundSendCommand(int command, u32 parameter1, u32 parameter2,
                                  u32 parameter3, u32 parameter4);

void func_02020a14(u32 value0, u32 value1, u32 value2, u32 value3,
                   u32 value4, u32 value5, u32 value6, u32 value7,
                   u32 unused, u32 value9)
{
    MaybeSoundSendCommand(0xe,
                          value0 | (unused << 16),
                          value2,
                          (value6 << 24) | (value7 << 22) | value5,
                          (value3 << 26) | (value1 << 24) |
                              (value9 << 16) | value4);
}
