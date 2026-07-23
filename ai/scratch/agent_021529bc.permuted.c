// PURPOSE: Marks a valid friend-code record by setting its ready flag.
extern int FriendCode_GetState_from_thumb(void *friend_code);
extern int FriendCode_GetFlags_from_thumb(void *friend_code);
extern void FriendCode_SetFlags_from_thumb(void *friend_code, int flags);

void func_021529bc(void *friend_code)
{
    if (FriendCode_GetState_from_thumb(friend_code) == 3) {
        int volatile flags = FriendCode_GetFlags_from_thumb(friend_code);
        flags |= 4;
        FriendCode_SetFlags_from_thumb(friend_code, flags);
    }
}
