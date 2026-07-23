// PURPOSE: Reads the packed values from a saved online record.
// The first argument selects an online record and the second receives three values.
// The record layout and validity flag are probably part of the game's online save data.

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct OnlineInfo {
    u8 unknown_00[0xC];
    u16 packedValues;
    u8 unknown_0E[0x14];
    u8 validFlag;
    u8 unknown_23;
} OnlineInfo;

extern int GlobalZ_GetOI(int slot, OnlineInfo *output);

int func_02060950(int slot, u8 *output)
{
    OnlineInfo info;

    GlobalZ_GetOI(slot, &info);
    if ((info.validFlag & 1) != 1) {
        return 0;
    }

    output[0] = (u8)(info.packedValues & 0x7F);
    output[1] = (u8)((info.packedValues >> 7) & 0x1F);
    output[2] = (u8)((info.packedValues >> 12) & 0x1F);
    return 1;
}
