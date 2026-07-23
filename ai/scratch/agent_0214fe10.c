// PURPOSE: Records backlight flags and sends the corresponding system command.

typedef struct SharedState {
    int state;
    int value1;
    int value2;
} SharedState;

typedef struct BacklightEntry {
    int flags;
    int unused;
} BacklightEntry;

extern SharedState data_02180448;
extern unsigned short data_02180470[];
extern BacklightEntry data_02180474[];

extern int func_021501d8(void);
extern void func_0214fa7c(unsigned int word);

int Pm_GetBacklightFlagsImpl(int index, int flags, int value1, int value2)
{
    if (func_021501d8() == 0) {
        return 1;
    }

    data_02180470[index * 4] = 0;
    data_02180448.value1 = value1;
    data_02180448.value2 = value2;
    data_02180474[index].flags = flags;
    func_0214fa7c((index & 0xff) | 0x03006500);
    return 0;
}
