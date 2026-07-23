// PURPOSE: Initializes a player profile from its saved identity data.
// Copies the supplied identity record and state into the profile.
// It then calculates the profile checksum with a temporary lookup table.

typedef unsigned int u32;

extern void GenerateProfileInfoCrcLookupTable(u32 *table, u32 polynomial);
extern u32 ComputeProfileInfoCrc(const u32 *table, const void *data, u32 size);

typedef struct FriendCodeData {
    u32 words[3];
} FriendCodeData;

typedef struct PlayerProfileInfo {
    char pad_00[0x10];
    FriendCodeData friendCode;
    u32 state;
    u32 flags;
    char pad_24[0x18];
    u32 crc;
} PlayerProfileInfo;

void func_021525f0(PlayerProfileInfo *profile, const FriendCodeData *friendCode,
                   u32 state)
{
    u32 table[0x100];

    profile->friendCode = *friendCode;
    profile->state = state;
    GenerateProfileInfoCrcLookupTable(table, 0xEDB88320);
    profile->crc = ComputeProfileInfoCrc(table, profile, 0x3c);
    profile->flags |= 1;
}
