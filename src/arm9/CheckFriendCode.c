// PURPOSE: Checks whether a typed friend code can be added to the saved friend list.
// The input is a twelve-digit friend code string.
// It rejects invalid and self-owned codes, then checks the existing friend slots.
// It returns 1 for a rejected code, 2 for a duplicate, and 0 for a new code.

typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;

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
    void *section_00;
    u8 padding_04[0x1c];
    void *online_data;
} SaveDataHolder;

extern SaveDataHolder *data_0217aa08;
extern int GlobalZ_GetOI(int slot, OnlineInfo *output);
extern u64 ConvertFriendCodeTo64_from_thumb(char *friend_code);
extern int Friend_VerifyChecksum_from_thumb(u32 profile_id, u32 checksum,
                                            u32 game_code);
extern u64 PlayerProfileInfo_GetProfileId_from_thumb(void *profile_info);
extern void FriendCode_SetProfileIdAndChecksum_from_thumb(
    FriendCode *friend_code, u32 profile_id, u32 checksum);
extern int FriendCode_HasNonzeroState_0_from_thumb(FriendCode *friend_code);
extern int FriendCode_SameAs_from_thumb(FriendCode *left, FriendCode *right);

int CheckFriendCode(char *friend_code_text)
{
    u64 friend_code_value;
    int result;
    u8 index;
    FriendCode friend_code;
    OnlineInfo info;
    FriendCode *entry;

    friend_code_value = ConvertFriendCodeTo64_from_thumb(friend_code_text);
    if (Friend_VerifyChecksum_from_thumb((u32)friend_code_value,
                                         (u32)(friend_code_value >> 32),
                                         0x414d434a) == 0) {
        return 1;
    }

    if (friend_code_value ==
        PlayerProfileInfo_GetProfileId_from_thumb(
            (u8 *)data_0217aa08->section_00 + 0x4c)) {
        return 1;
    }

    FriendCode_SetProfileIdAndChecksum_from_thumb(
        &friend_code, (u32)friend_code_value,
        (u32)(friend_code_value >> 32));

    entry = (FriendCode *)((u8 *)data_0217aa08->online_data + 0x874);
    result = -1;
    for (index = 0; index < 60; index++) {
        GlobalZ_GetOI(index, &info);
        if (info.valid == 1) {
            FriendCode *candidate =
                (FriendCode *)((u8 *)entry + (u32)index * 12);

            if (FriendCode_HasNonzeroState_0_from_thumb(candidate) != 0) {
                if (FriendCode_SameAs_from_thumb(candidate, &friend_code) != 0) {
                    result = (signed char)index;
                    break;
                }
            }
        }
    }

    return result != -1 ? 2 : 0;
}
