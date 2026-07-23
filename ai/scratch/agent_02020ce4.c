// PURPOSE: Sends sound command twelve with two supplied values.
// The first two arguments are passed through as sound-command parameters.
// The third argument is probably another command parameter.

extern void func_02020870(int value0, int value1, int command,
                          int value2, int parameter);

void func_02020ce4(int value0, int value1, int value2)
{
    func_02020870(value0, value1, 12, value2, 2);
}
