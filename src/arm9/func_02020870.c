// PURPOSE: Sends a sound command with the supplied parameters.
// The first, second, third, and fourth values are forwarded to the sound system.
// The fifth value probably supplies the high byte of the command identifier.
extern void MaybeSoundSendCommand(int command, unsigned int packed, int second, int third, int fourth);

void func_02020870(unsigned int id, int second, int third, int fourth, unsigned int high_byte) {
    MaybeSoundSendCommand(7, id | (high_byte << 24), second, third, fourth);
}
