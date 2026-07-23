// PURPOSE: Sends sound command nine with three supplied values.
// The first two values are forwarded directly to the sound command.
// The third value probably supplies its fourth parameter.

extern void func_02020870(unsigned int id, int second, int third, int fourth,
                          unsigned int high_byte);

void func_02020cbc(unsigned int id, int second, int fourth)
{
    func_02020870(id, second, 9, fourth, 1);
}
