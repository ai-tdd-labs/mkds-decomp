// PURPOSE: Prepares a player profile for saving.
// The profile supplied by the caller has its transient flag cleared.
// It then probably rebuilds the profile checksum using a temporary lookup table.

typedef unsigned int u32;

extern void GenerateProfileInfoCrcLookupTable(u32 *table, u32 polynomial);
extern u32 ComputeProfileInfoCrc(const u32 *table, const void *data, u32 size);

typedef struct PlayerProfileInfo {
    char pad_00[0x20];
    u32 flags;
    char pad_24[0x18];
    u32 crc;
} PlayerProfileInfo;

void PlayerProfileInfo_PrepareForSave_from_thumb(PlayerProfileInfo *profile)
{
    // Clear the unsaved/transient low flag before calculating the checksum.
    profile->flags &= ~1;
    {
        u32 table[0x100];

        GenerateProfileInfoCrcLookupTable(table, 0xEDB88320);
        profile->crc = ComputeProfileInfoCrc(table, profile, 0x3c);
    }
}
