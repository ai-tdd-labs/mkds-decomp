// PURPOSE: Updates an online record's status flag when the record is valid.
// Reads the selected online-information record into a temporary buffer.
// The second argument probably controls the record's bit-three status flag.

typedef struct OnlineInfo {
    unsigned char unknown_00[0x22];
    unsigned char valid : 1;
    unsigned char unknown_01 : 2;
    unsigned char status : 1;
    unsigned char remaining_flags : 4;
    unsigned char unknown_23;
} OnlineInfo;

extern int GlobalZ_GetOI(int slot, OnlineInfo *output);
extern void GlobalZ_SetOI(int slot, const OnlineInfo *input);

int func_02060880(int slot, int enabled)
{
    OnlineInfo info;

    GlobalZ_GetOI(slot, &info);
    if (info.valid == 1) {
        info.status = enabled != 0;
        GlobalZ_SetOI(slot, &info);
        return 1;
    }
    return 0;
}
