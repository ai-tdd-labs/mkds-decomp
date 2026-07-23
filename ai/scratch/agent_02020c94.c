// PURPOSE: Sends a sound command with three supplied values.
// The values are forwarded to the sound system with command 25.
// The final command byte is probably set to one.

extern void func_02020870(unsigned int id, int second, int third, int fourth,
                          unsigned int high_byte);

void func_02020c94(unsigned int id, int second, int third)
{
    func_02020870(id, second, 25, third, 1);
}
