// PURPOSE: Returns the record's secondary flag when the record is valid.
// Reads the selected online-information record into a temporary buffer.
// The low flag probably gates the bit-three status returned by this helper.

typedef struct OnlineInfo {
    unsigned char unknown_00[0x22];
    unsigned char valid : 1;
    unsigned char unknown_01 : 2;
    unsigned char status : 1;
    unsigned char remaining_flags : 4;
    unsigned char unknown_23;
} OnlineInfo;

extern int GlobalZ_GetOI(int slot, OnlineInfo *output);

int func_02060afc(int slot)
{
    OnlineInfo info;

    GlobalZ_GetOI(slot, &info);
    return info.valid == 1 ? info.status : 0;
}
