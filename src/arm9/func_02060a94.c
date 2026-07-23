// PURPOSE: Returns the saved online value when its validity bit is set.
// Takes an online-record slot and fills a temporary record through the loader.
// Probably returns the halfword at offset two, or -1 when bit zero at offset 0x22 is clear.

typedef struct OnlineInfo {
    unsigned char unknown_00[2];
    unsigned short value_02;
    unsigned char unknown_04[0x1E];
    unsigned char valid_22;
    unsigned char unknown_23;
} OnlineInfo;

extern int GlobalZ_GetOI(int slot, OnlineInfo *output);

int func_02060a94(int slot) {
    volatile OnlineInfo info;

    GlobalZ_GetOI(slot, (OnlineInfo *)&info);
    return ((((unsigned int)info.valid_22 << 31) >> 31) == 1)
        ? info.value_02
        : -1;
}
