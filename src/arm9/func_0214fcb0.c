// PURPOSE: Maps a small selector to a command code and forwards two values to the shared command sender.

extern int func_0214fe88(unsigned int command, int value1, int value2);

int func_0214fcb0(int command, int value1, int value2)
{
    int mappedCommand;

    switch (command) {
    case 1:
        mappedCommand = 1;
        break;
    case 3:
        mappedCommand = 2;
        break;
    case 2:
        mappedCommand = 3;
        break;
    default:
        mappedCommand = 0;
        break;
    }

    if (mappedCommand == 0) {
        return 0xffff;
    }

    return func_0214fe88(mappedCommand, value1, value2);
}
