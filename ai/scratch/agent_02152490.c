// PURPOSE: Copies a player's friend code into a destination code.
// The first argument is probably a player profile and the second is a friend-code buffer.
// A profile with state one produces a code with its profile ID and state three.

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct FriendCode {
    u32 words[3];
} FriendCode;

typedef struct PlayerProfileInfo {
    u8 unknown_00[4];
    FriendCode friend_code;
    u8 unknown_10[0xc];
    u32 profile_id;
} PlayerProfileInfo;

extern void Mem_CpuFill8(void *destination, int value, u32 size);
extern int PlayerProfileInfo_FriendCode2_HasState1_from_thumb(
    PlayerProfileInfo *profile);
extern void FriendCode_SetProfileId_from_thumb(FriendCode *friend_code,
                                                u32 profile_id);
extern void FriendCode_SetState_from_thumb(FriendCode *friend_code, int state);

void PlayerProfileInfo_CopyFriendCode_from_thumb(PlayerProfileInfo *profile,
                                                  FriendCode *friend_code)
{
    Mem_CpuFill8(friend_code, 0, 0xc);

    if (PlayerProfileInfo_FriendCode2_HasState1_from_thumb(profile)) {
        FriendCode_SetProfileId_from_thumb(friend_code, profile->profile_id);
        FriendCode_SetState_from_thumb(friend_code, 3);
        return;
    }

    *friend_code = profile->friend_code;
}
