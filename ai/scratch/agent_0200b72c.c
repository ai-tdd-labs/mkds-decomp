// PURPOSE: Finds an enabled bit while advancing the global counter.
// The input is probably a bit mask used to select an allowed counter value.
// Zero and the special 0x8000 result are rejected.

typedef unsigned short u16;

extern char *data_0216fde8;
extern int func_02143280(int value);

int func_0200b72c(int value)
{
    value = func_02143280(value);
    if (value == 0x8000 || value == 0) {
        return 0;
    }

    *(u16 *)(data_0216fde8 + 0x584) += 1;

    do {
        *(u16 *)(data_0216fde8 + 0x584) += 1;
        if (*(u16 *)(data_0216fde8 + 0x584) > 0x10) {
            *(u16 *)(data_0216fde8 + 0x584) = 1;
        }
    } while ((value & (1 << (*(u16 *)(data_0216fde8 + 0x584) - 1))) == 0);

    return 1;
}
