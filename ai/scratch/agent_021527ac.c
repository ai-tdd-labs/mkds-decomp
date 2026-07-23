// PURPOSE: Creates a player profile from a thumbnail.
// The profile and thumbnail pointer are supplied by the caller.
// It initializes the embedded friend code and records a checksum.

typedef unsigned int u32;

typedef struct FriendCode {
    u32 words[3];
} FriendCode;

typedef struct PlayerProfileInfo {
    u32 size;
    FriendCode friendCode;
    u32 friendCodeState;
    u32 unknown_14;
    u32 unknown_18;
    u32 unknown_1c;
    u32 flags;
    void *thumbnail;
    u32 unknown_28[5];
    u32 crc;
} PlayerProfileInfo;

extern void Mem_CpuFill8(void *destination, int value, u32 size);
extern void FriendCode_CreateFrom_from_thumb(FriendCode *friendCode);
extern void FriendCode_SetState_from_thumb(FriendCode *friendCode, int state);
extern void GenerateProfileInfoCrcLookupTable(u32 *table, u32 polynomial);
extern u32 ComputeProfileInfoCrc(const u32 *table, const void *data, u32 size);

void PlayerProfileInfo_Create_from_thumb(PlayerProfileInfo *profile, void *thumbnail)
{
    u32 table[0x100];

    Mem_CpuFill8(profile, 0, 0x40);
    profile->size = 0x40;
    profile->unknown_1c = 0;
    profile->thumbnail = thumbnail;
    FriendCode_CreateFrom_from_thumb(&profile->friendCode);
    FriendCode_SetState_from_thumb((FriendCode *)&profile->friendCodeState, 0);
    GenerateProfileInfoCrcLookupTable(table, 0xEDB88320);
    profile->crc = ComputeProfileInfoCrc(table, profile, 0x3c);
    profile->flags |= 1;
}
