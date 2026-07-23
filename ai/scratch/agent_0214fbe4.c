// PURPOSE: Sends a command selected by two small mode values.
// The first two arguments choose one of six command numbers.
// The final two arguments are forwarded to the shared command sender.
// Unsupported combinations return an error value.

extern int func_0214fe88(unsigned int command, int value1, int value2);

int func_0214fbe4(int mode, int state, int value1, int value2)
{
    unsigned int command;

    command = 0;
    if (mode == 0) {
        if (state == 1) {
            command = 6;
        }
        if (state == 0) {
            command = 7;
        }
    } else if (mode == 1) {
        if (state == 1) {
            command = 4;
        }
        if (state == 0) {
            command = 5;
        }
    } else if (mode == 2) {
        if (state == 1) {
            command = 8;
        }
        if (state == 0) {
            command = 9;
        }
    }

    if (command == 0) {
        return 0xffff;
    }

    return func_0214fe88(command, value1, value2);
}
