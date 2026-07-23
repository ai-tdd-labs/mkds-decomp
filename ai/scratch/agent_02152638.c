// PURPOSE: Checks whether the profile has the expected friend code.
// The profile probably stores its embedded friend-code bytes at offset 0x10.
// A temporary 24-byte record supplies the expected packed value.
// The function returns one when the state and values pass their checks.

typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct {
    u32 words[6];
} StructDWRecord;

typedef struct {
    char unknown_00[0x10];
    char friend_code[0xc];
} PlayerProfileInfo;

extern int FriendCode_GetState_from_thumb(void *a0);
extern void StructDW_SomeFn_GetSomething_from_thumb(StructDWRecord *record);
extern u64 FriendCode_GetSomePackedValue_from_thumb(void *a0);

int PlayerProfileInfo_SomeFn_4_from_thumb(PlayerProfileInfo *profile)
{
    StructDWRecord record;

    if (FriendCode_GetState_from_thumb(profile->friend_code) == 0) {
        return 1;
    }

    StructDW_SomeFn_GetSomething_from_thumb(&record);
    if (record.words[4] == 0) {
        return 0;
    }

    if (*(u64 *)record.words == FriendCode_GetSomePackedValue_from_thumb(profile->friend_code)) {
        return 1;
    }

    return 0;
}
