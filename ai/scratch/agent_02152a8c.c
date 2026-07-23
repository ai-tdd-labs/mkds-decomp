typedef unsigned int u32;

typedef struct FriendCode {
    u32 flags;
    u32 profile_id;
} FriendCode;

extern void FriendCode_SetFlagsImpl_from_thumb(FriendCode *friend_code,
                                                u32 flags, u32 shift,
                                                u32 mask);

// PURPOSE: Sets a friend-code profile ID and its associated flags.
void FriendCode_SetProfileIdAndFlags_from_thumb(FriendCode *friend_code,
                                                 u32 profile_id, u32 flags)
{
    u32 shift = 0;

    FriendCode_SetFlagsImpl_from_thumb(friend_code, flags, shift, 0x7FF);
    friend_code->profile_id = profile_id;
}
