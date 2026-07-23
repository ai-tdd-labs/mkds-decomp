// PURPOSE: Initializes a friend code record with a profile and active state.
// The first argument is probably a 12-byte friend code record.
// The second argument supplies its profile ID.

extern void Mem_CpuFill8(void *destination, unsigned int value,
                         unsigned int size);
extern void FriendCode_SetProfileId_from_thumb(void *record,
                                               unsigned int profileId);
extern void FriendCode_SetState_from_thumb(void *record, int state);

void func_02152468(void *record, unsigned int profileId)
{
    Mem_CpuFill8(record, 0, 0xc);
    FriendCode_SetProfileId_from_thumb(record, profileId);
    FriendCode_SetState_from_thumb(record, 3);
}
