// PURPOSE: Creates a friend code from a profile and a number.
// The first argument receives the new code.
// The second argument is probably an identifier used with the current tick.

typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct FriendCodeValues {
    u32 profile_id_a;
    u32 flags_a;
    u32 profile_id_b;
    u32 flags_b;
    u32 use_first;
    u32 unused;
} FriendCodeValues;

extern u32 Os_GetTick(void);
extern void StructDW_SomeFn_GetSomething_from_thumb(FriendCodeValues *values);
extern void FriendCode_SetProfileIdAndFlags_from_thumb(void *friend_code,
                                                        u32 profile_id, u32 flags);
extern u64 Multiply64(u64 left, u64 right);
extern void FriendCode_SetCrcChecksum_from_thumb(void *friend_code,
                                                  u32 high, u32 low);
extern void FriendCode_SetState_from_thumb(void *friend_code, int state);

void FriendCode_CreateFrom_from_thumb(void *friend_code, u32 identifier)
{
    FriendCodeValues values;
    u32 tick = Os_GetTick();
    u64 checksum;

    StructDW_SomeFn_GetSomething_from_thumb(&values);
    if (values.use_first != 0) {
        FriendCode_SetProfileIdAndFlags_from_thumb(friend_code, values.profile_id_a,
                                                    values.flags_a);
    } else {
        FriendCode_SetProfileIdAndFlags_from_thumb(friend_code, values.profile_id_b,
                                                    values.flags_b);
    }

    checksum = Multiply64(((u64)identifier << 32) | tick,
                           0x5d588b656c078965ULL) + 0x00269ec3ULL;
    FriendCode_SetCrcChecksum_from_thumb(friend_code, (u32)(checksum >> 32),
                                         (u32)checksum);
    FriendCode_SetState_from_thumb(friend_code, 1);
}
