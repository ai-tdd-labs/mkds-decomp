// PURPOSE: Formats a friend code according to its current state.
// The first argument is probably a player profile and the second is a friend-code object.
// State two writes its packed code into temporary storage; state one builds its display text.

typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct PlayerProfileInfo {
    char unknown_00[0x24];
    u32 profile_id;
} PlayerProfileInfo;

extern int FriendCode_GetState_from_thumb(void *a0);
extern u64 FriendCode_GetFriendCodePacked_from_thumb(void *a0);
extern void PrintfUll_from_thumb(u64 value, void *context);
extern void FriendCode_SomeFn_7_from_thumb(int a0, unsigned int a1, char *a2);

void PlayerProfileInfo_SomeFn_3_from_thumb(PlayerProfileInfo *profile, void *friend_code)
{
    char buffer[0x24];

    if (FriendCode_GetState_from_thumb(friend_code) == 3) {
        return;
    }

    if (FriendCode_GetState_from_thumb(friend_code) == 2) {
        PrintfUll_from_thumb(FriendCode_GetFriendCodePacked_from_thumb(friend_code), buffer);
        return;
    }

    if (FriendCode_GetState_from_thumb(friend_code) == 1) {
        FriendCode_SomeFn_7_from_thumb((int)friend_code, profile->profile_id, buffer + 0xd);
    }
}
