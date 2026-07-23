// PURPOSE: Gets the saved online record value when its flag is set.
// Takes an online-record slot and reads that record into a temporary buffer.
// Returns the record's value when bit zero of its status flag is set, otherwise -1.

typedef struct OnlineInfo {
    unsigned char padding_00[6];
    unsigned short value_06;
    unsigned char padding_08[0x1A];
    volatile unsigned char status_22;
    unsigned char padding_23;
} OnlineInfo;

extern int GlobalZ_GetOI(int slot, OnlineInfo *output);

int func_02060a2c(int slot) {
    OnlineInfo info;

    GlobalZ_GetOI(slot, &info);
    if ((((unsigned int)info.status_22 << 31) >> 31) == 1) {
        return info.value_06;
    }
    return -1;
}
