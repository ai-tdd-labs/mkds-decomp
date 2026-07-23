// PURPOSE: Builds one save-profile summary for the profile selection screen.
// The destination receives profile settings, emblem data, unlock flags, and a friend code.
// The emblem is copied only when the active profile allows it; otherwise its buffer is cleared.
// A shared-system mode can also suppress the copied friend code.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct PlayerProfileInfo {
    u8 data[0x4c];
} PlayerProfileInfo;

typedef struct SystemProfileData {
    u8 pad_00[0x0c];
    u8 profileSettings[0x14];
    u8 unlockFlags[4];
    u16 profileValue;
    u8 pad_26[0x0b];
    u8 unusedFlags : 3;
    u8 customEmblemBlocked : 1;
    u8 remainingFlags : 4;
    u8 pad_32[0x1a];
    PlayerProfileInfo playerProfileInfo;
} SystemProfileData;

typedef struct PlayerProfileData {
    u8 pad_00[4];
    u8 hasCustomEmblem : 1;
    u8 remainingFlags : 7;
    u8 pad_05[3];
    u8 customEmblem[0x200];
} PlayerProfileData;

typedef struct SaveDataRoot {
    SystemProfileData *systemProfile;
    PlayerProfileData *playerProfile;
} SaveDataRoot;

typedef struct SystemContext {
    u32 sharedValue;
    u32 language;
} SystemContext;

typedef struct StructTK {
    u8 profileSettings[0x14];
    u8 customEmblem[0x200];
    u8 hasCustomEmblem;
    u8 pad_215;
    u16 profileValue;
    u8 friendCode[0x0c];
    u8 unlockFlags[4];
    u8 sharedValue : 4;
    u8 language : 4;
    u8 worstStarRank;
    u8 pad_22a[2];
} StructTK;

extern SaveDataRoot *data_0217aa08;
extern SystemContext *data_021759d0;

extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);
extern void Mem_CpuFill8(void *destination, int value, u32 size);
extern int GetWorstStarRank_from_thumb(void);
extern void PlayerProfileInfo_CopyFriendCode_from_thumb(
    PlayerProfileInfo *profile, void *friendCode);

void StructTK_SomeFn_from_thumb(StructTK *result)
{
    Mem_CpuCopy8(data_0217aa08->systemProfile->profileSettings,
                 result->profileSettings, 0x14);

    if (data_0217aa08->playerProfile->hasCustomEmblem &&
        !data_0217aa08->systemProfile->customEmblemBlocked) {
        result->hasCustomEmblem = 1;
        Mem_CpuCopy8(data_0217aa08->playerProfile->customEmblem,
                     result->customEmblem, 0x200);
    } else {
        result->hasCustomEmblem = 0;
        Mem_CpuFill8(result->customEmblem, 0, 0x200);
    }

    Mem_CpuCopy8(data_0217aa08->systemProfile->unlockFlags,
                 result->unlockFlags, 4);

    result->sharedValue = data_021759d0->sharedValue;
    result->language = data_021759d0->language;
    result->profileValue = data_0217aa08->systemProfile->profileValue;
    result->worstStarRank = GetWorstStarRank_from_thumb();

    if (*(volatile u16 *)0x027ffc40 == 2) {
        Mem_CpuFill8(result->friendCode, 0, 0x0c);
        return;
    }

    PlayerProfileInfo_CopyFriendCode_from_thumb(
        &data_0217aa08->systemProfile->playerProfileInfo,
        result->friendCode);
}
