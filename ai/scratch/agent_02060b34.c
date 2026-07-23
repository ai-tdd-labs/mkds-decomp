// PURPOSE: Checks whether an online record has its status flag set.
// Reads the saved online information for the requested slot.
// The record layout is only known through its one-bit status field at offset 0x22.

typedef struct OnlineInfo {
    unsigned char unknown_00[0x22];
    unsigned char status : 1;
    unsigned char unknown_23;
} OnlineInfo;

extern int GlobalZ_GetOI(int slot, OnlineInfo *output);

int func_02060b34(int slot) {
    OnlineInfo info;

    GlobalZ_GetOI(slot, &info);
    return info.status == 1;
}
