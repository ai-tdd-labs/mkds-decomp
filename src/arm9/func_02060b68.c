// PURPOSE: Clears the active flag on saved online records that have a friend code.

typedef struct OnlineInfo {
    unsigned char unknown_00[0x22];
    unsigned char valid : 1;
    unsigned char active : 1;
    unsigned char remaining_flags : 6;
    unsigned char unknown_23;
} OnlineInfo;

typedef struct SaveDataHolder {
    unsigned char unknown_00[0x20];
    void *online_data;
} SaveDataHolder;

extern SaveDataHolder *data_0217aa08;
extern int GlobalZ_GetOI(int slot, OnlineInfo *output);
extern void GlobalZ_SetOI(int slot, const OnlineInfo *input);
extern int FriendCode_SomeFn_from_thumb(void *a0);

void func_02060b68(void)
{
    unsigned char slot;
    OnlineInfo info;

    for (slot = 0; slot < 60; slot++) {
        GlobalZ_GetOI(slot, &info);
        if (info.valid == 1 && info.active == 1) {
            if (FriendCode_SomeFn_from_thumb((unsigned char *)data_0217aa08->online_data + 0x874 + slot * 12) != 0) {
                info.active = 0;
                GlobalZ_SetOI(slot, &info);
            }
        }
    }
}
