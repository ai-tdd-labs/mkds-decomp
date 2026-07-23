// PURPOSE: Prints a saved friend's code when the selected online record is active.
// It loads the selected online-information record into a local buffer.
// The function probably prints the friend code to the supplied output context.

typedef unsigned char u8;
typedef unsigned long long u64;

typedef struct OnlineInfo {
    u8 unknown_00[0x22];
    u8 valid : 1;
    u8 active : 1;
    u8 remaining_flags : 6;
    u8 unknown_23;
} OnlineInfo;

typedef struct SaveDataHolder {
    u8 padding[0x20];
    void *friend_list;
} SaveDataHolder;

extern int GlobalZ_GetOI(int slot, OnlineInfo *output);
extern int FriendCode_HasNonzeroState_from_thumb(void *friend_code);
extern u64 FriendCode_GetFriendCodePacked_0_from_thumb(void *friend_code);
extern void PrintfUll_from_thumb(u64 value, void *context);
extern SaveDataHolder *data_0217aa08;

int func_02060468(int slot, void *context)
{
    OnlineInfo info;
    void *friend_code;
    int result = 0;
    int should_print;

    GlobalZ_GetOI(slot, &info);
    friend_code = (char *)data_0217aa08->friend_list + 0x874 + slot * 12;
    if (info.valid == 1) {
        if (info.active == 1) {
            if (FriendCode_HasNonzeroState_from_thumb(friend_code) != 0) {
                should_print = 1;
                goto state_done;
            }
        }
    }
    should_print = 0;
state_done:
    if (should_print != 0) {
        PrintfUll_from_thumb(
            FriendCode_GetFriendCodePacked_0_from_thumb(friend_code), context);
        result = 1;
    }
    return result;
}
