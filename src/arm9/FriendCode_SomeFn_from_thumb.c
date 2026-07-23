// PURPOSE: Checks whether a friend-code object is ready for use.
// The argument is probably a friend-code state object.
// It succeeds only in state 3 when flag bit 4 is set.

extern int FriendCode_GetState_from_thumb(void *a0);
extern int FriendCode_GetFlags_from_thumb(void *a0);

int FriendCode_SomeFn_from_thumb(void *a0)
{
    if (FriendCode_GetState_from_thumb(a0) == 3) {
        if ((FriendCode_GetFlags_from_thumb(a0) & 4) == 4) { // required flag
            return 1;
        }
        return 0;
    }
    return 0;
}
