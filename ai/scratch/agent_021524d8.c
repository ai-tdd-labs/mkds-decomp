// PURPOSE: Initializes a friend code record with its profile data.
// The record is cleared before its profile ID and checksum are stored.
// The final state value marks the record as ready.

extern void Mem_CpuFill8(void *destination, unsigned int value,
                         unsigned int size);
extern void FriendCode_SetFriendCodeValues_from_thumb(void *record,
                                                       unsigned int profileId,
                                                       unsigned int checksum);
extern void FriendCode_SetState_from_thumb(void *record, int state);

void FriendCode_SetProfileIdAndChecksum_from_thumb(void *record,
                                                    unsigned int profileId,
                                                    unsigned int checksum)
{
    Mem_CpuFill8(record, 0, 0xc);
    FriendCode_SetFriendCodeValues_from_thumb(record, profileId, checksum);
    FriendCode_SetState_from_thumb(record, 2);
}
