// PURPOSE: Checks whether a friend code matches a generated record.
// The argument is probably a friend-code object.
// A temporary 24-byte record chooses one of two packed-code values.

typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct {
    u32 words[6];
} StructDWRecord;

extern void StructDW_SomeFn_GetSomething_from_thumb(StructDWRecord *record);
extern u64 FriendCode_GetSomePackedValue_from_thumb(void *friend_code);

int func_021526e4(void *friend_code)
{
    StructDWRecord record;
    u64 packed;

    StructDW_SomeFn_GetSomething_from_thumb(&record);

    packed = FriendCode_GetSomePackedValue_from_thumb(friend_code);
    if (record.words[4] != 0) {
        if (packed == *(u64 *)&record.words[0]) {
            return 1;
        }
        return 0;
    }

    if (packed == *(u64 *)&record.words[2]) {
        return 1;
    }
    return 0;
}
