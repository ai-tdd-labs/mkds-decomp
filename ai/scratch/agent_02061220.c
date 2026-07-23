// PURPOSE: Prints the current player profile ID.
// The argument is probably the output context used by the profile-ID formatter.
// It reads the active profile from the global game state and forwards its ID.

typedef unsigned long long u64;

extern void **data_0217aa08;
extern u64 PlayerProfileInfo_GetProfileId_from_thumb(void *profileInfo);
extern void PrintfUll_from_thumb(u64 value, void *context);

void func_02061220(void *context)
{
    PrintfUll_from_thumb(
        PlayerProfileInfo_GetProfileId_from_thumb((char *)*data_0217aa08 + 0x4c),
        context);
}
