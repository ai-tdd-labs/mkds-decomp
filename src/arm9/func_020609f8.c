// PURPOSE: Returns an online record value when its status flag is set.
// Reads the online information for the requested slot.
// The record is probably a saved network profile.

typedef unsigned char u8;

typedef struct OnlineInfo {
    u8 data[0x22];
    u8 valid;
    u8 trailingByte;
} OnlineInfo;

extern int GlobalZ_GetOI(int slot, OnlineInfo *output);

int func_020609f8(int slot)
{
    volatile OnlineInfo info;

    GlobalZ_GetOI(slot, (OnlineInfo *)&info);
    if ((((unsigned int)info.valid << 31) >> 31) == 1) {
        return *(volatile unsigned short *)&info.data[8];
    }
    return -1;
}
