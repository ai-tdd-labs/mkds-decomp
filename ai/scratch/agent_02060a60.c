// PURPOSE: Returns the saved online record value when its flag is set.
// Reads the online-information record selected by the requested slot.
// The record layout and flag meaning are probably still unknown.

typedef struct OnlineInfo {
    unsigned char unknown_00[4];
    unsigned short value;
    unsigned char unknown_06[0x1C];
    unsigned char flag;
    unsigned char unknown_23;
} OnlineInfo;

extern int GlobalZ_GetOI(int slot, OnlineInfo *output);

int func_02060a60(int slot) {
    OnlineInfo info;
    int flag;

    GlobalZ_GetOI(slot, &info);
    flag = info.flag;
    flag = flag << 31;
    flag = (unsigned int)flag >> 31;
    return flag == 1 ? info.value : -1;
}
