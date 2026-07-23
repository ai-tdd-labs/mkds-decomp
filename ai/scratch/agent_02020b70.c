// PURPOSE: Sends a packed sound command.
//
// The seven input values provide five bit fields and two command parameters.
// The bit fields are combined into the sound system's packed command word.
// The final sound argument is always zero, probably selecting a default mode.

extern void MaybeSoundSendCommand(int command, unsigned int packed, int second, int third, int fourth);

void func_02020b70(unsigned int bit0, unsigned int bit1, int second, int third,
                   unsigned int bit2, unsigned int bit3, unsigned int bit4)
{
    MaybeSoundSendCommand(0x11, second, third,
                          (bit0 << 31) | (bit1 << 30) | (bit2 << 29) |
                              (bit3 << 28) | (bit4 << 27),
                          0);
}
