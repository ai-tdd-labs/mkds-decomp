// PURPOSE: Finds a saved friend code in the friend list.
typedef unsigned char u8;
typedef unsigned int u32;

typedef struct OnlineInfo {
    u8 data[0x22];
    u8 valid : 1;
    u8 remaining_flags : 7;
    u8 trailing_byte;
} OnlineInfo;

typedef struct FriendCode {
    u32 words[3];
} FriendCode;

typedef struct SaveDataHolder {
    u8 padding_00[0x20];
    void *online_data;
} SaveDataHolder;

extern SaveDataHolder *data_0217aa08;
extern int GlobalZ_GetOI(int slot, OnlineInfo *output);
extern int FriendCode_HasNonzeroState_0_from_thumb(FriendCode *friend_code);
extern int FriendCode_SameAs_from_thumb(FriendCode *left, FriendCode *right);

int FindSomeOI_FriendCode_Index(FriendCode *friend_code)
{
    int result;
    u8 index;
    OnlineInfo info;
    FriendCode *entry;

    entry = (FriendCode *)((u8 *)data_0217aa08->online_data + 0x874);
    result = -1;
    for (index = 0; index < 60; index++) {
        GlobalZ_GetOI(index, &info);
        if (info.valid == 1) {
            FriendCode *candidate =
                (FriendCode *)((u8 *)entry + (u32)index * 12);

            if (FriendCode_HasNonzeroState_0_from_thumb(candidate) != 0) {
                if (FriendCode_SameAs_from_thumb(candidate, friend_code) != 0) {
                    result = (signed char)index;
                    break;
                }
            }
        }
    }
    return result;
}
