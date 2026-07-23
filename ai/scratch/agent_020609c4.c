// PURPOSE: Returns the saved online value when its valid bit is set.
// Reads one probably saved online-information record for the given slot.
// The record layout is only known at the fields used here.

typedef unsigned char u8;

typedef struct OnlineInfo {
    u8 data[0x0a];
    unsigned short value;
    u8 unknown_0c[0x16];
    u8 valid : 1;
    u8 remainingFlags : 7;
    u8 trailingByte;
} OnlineInfo;

extern int GlobalZ_GetOI(int slot, OnlineInfo *output);

int func_020609c4(int slot)
{
    volatile OnlineInfo info;

    GlobalZ_GetOI(slot, (OnlineInfo *)&info);
    if (info.valid == 1) {
        return *(volatile unsigned short *)&info.data[0x0a];
    }
    return -1;
}
