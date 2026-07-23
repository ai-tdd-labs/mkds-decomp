/* PURPOSE: Checks whether the current player profile has an ID.
 * Takes no arguments. It follows the shared player-data pointer to the
 * profile information at offset 0x4c and returns 1 when its 64-bit profile
 * ID is nonzero, otherwise 0. The exact outer object types are uncertain. */

typedef unsigned long long u64;

extern void **data_0217aa08;
extern u64 PlayerProfileInfo_GetProfileId_from_thumb(void *profileInfo);

int func_02061250(void)
{
    void *profileInfo = (char *)*data_0217aa08 + 0x4c;

    return PlayerProfileInfo_GetProfileId_from_thumb(profileInfo) != 0;
}
