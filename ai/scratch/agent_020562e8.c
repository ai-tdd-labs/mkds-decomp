/* PURPOSE: Aggregates unlock flags across the active save profiles.
 * The shared flag bytes record both the intersection and union of the
 * profiles, while the final two bytes track the highest and lowest kart
 * unlock counts.
 */

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct SaveProfile {
    u8 pad000[0x224];
    u8 secretFlags[4];
    u8 pad228[0x22c - 0x228];
} SaveProfile;

typedef struct SaveContext {
    u8 pad0000[0x45c];
    SaveProfile profiles[8];
    u8 pad15bc[0x15f6 - 0x15bc];
    u8 activeProfileMask;
} SaveContext;

typedef struct SaveDataHolder {
    u8 pad00[0x30];
    u8 commonSecretFlags[4];
    u8 combinedSecretFlags[4];
    u8 highestKartUnlockCount;
    u8 lowestKartUnlockCount;
} SaveDataHolder;

extern SaveContext *data_0217aa00;
extern SaveDataHolder *data_0217aa08;

extern void CleanSaveDataHolderFlagBytes_from_thumb(void);
extern int CheckExtraKartUnlockFlagsWith_from_thumb(void *saveData);

void func_020562e8(void) {
    u8 profileIndex;
    u8 flagByteIndex;

    CleanSaveDataHolderFlagBytes_from_thumb();

    for (profileIndex = 0; profileIndex < 8; profileIndex++) {
        int kartUnlockCount;

        if ((data_0217aa00->activeProfileMask & (1 << profileIndex)) == 0) {
            continue;
        }

        for (flagByteIndex = 0; flagByteIndex < 4; flagByteIndex++) {
            if (profileIndex == 0) {
                data_0217aa08->commonSecretFlags[flagByteIndex] =
                    data_0217aa00->profiles[profileIndex]
                        .secretFlags[flagByteIndex];
                data_0217aa08->combinedSecretFlags[flagByteIndex] =
                    data_0217aa00->profiles[profileIndex]
                        .secretFlags[flagByteIndex];
            } else {
                data_0217aa08->commonSecretFlags[flagByteIndex] &=
                    data_0217aa00->profiles[profileIndex]
                        .secretFlags[flagByteIndex];
                data_0217aa08->combinedSecretFlags[flagByteIndex] |=
                    data_0217aa00->profiles[profileIndex]
                        .secretFlags[flagByteIndex];
            }
        }

        kartUnlockCount = CheckExtraKartUnlockFlagsWith_from_thumb(
            data_0217aa00->profiles[profileIndex].secretFlags);

        if (profileIndex == 0) {
            data_0217aa08->highestKartUnlockCount = kartUnlockCount;
            data_0217aa08->lowestKartUnlockCount = kartUnlockCount;
        } else {
            if ((u32)kartUnlockCount >
                data_0217aa08->highestKartUnlockCount) {
                data_0217aa08->highestKartUnlockCount = kartUnlockCount;
            }
            if ((u32)kartUnlockCount <
                data_0217aa08->lowestKartUnlockCount) {
                data_0217aa08->lowestKartUnlockCount = kartUnlockCount;
            }
        }
    }
}
