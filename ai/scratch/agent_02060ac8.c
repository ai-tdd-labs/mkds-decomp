// PURPOSE: Returns the saved online record's first value when its flag is set.
// Reads one saved online-information record into a temporary buffer.
// The status bit probably indicates whether the first halfword is usable.

typedef unsigned char u8;

typedef struct OnlineInfo {
    u8 data[0x22];
    u8 valid : 1;
    u8 remainingFlags : 7;
    u8 trailingByte;
} OnlineInfo;

extern int GlobalZ_GetOI(int slot, OnlineInfo *output);

int func_02060ac8(int slot)
{
    volatile OnlineInfo info;

    GlobalZ_GetOI(slot, (OnlineInfo *)&info);
    if (info.valid == 1) {
        return *(volatile unsigned short *)&info.data[0];
    }
    return -1;
}
