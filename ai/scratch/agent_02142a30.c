// PURPOSE: Checks the current wireless receive state.
// Returns the wireless initialization result when setup is still pending.
// Otherwise invalidates the shared status word and probably maps its value to a state code.

typedef unsigned int u32;
typedef unsigned short u16;

extern int Wm_CheckInitialized(void);
extern void DC_InvalidateRangeNoClean(void *start, u32 length);
extern void **data_0217eed4;

int func_02142a30(void)
{
    int result = Wm_CheckInitialized();

    if (result != 0) {
        return result;
    }

    DC_InvalidateRangeNoClean(data_0217eed4[0][1], 2);

    if (*(u16 *)data_0217eed4[0][1] <= 1) {
        return 3;
    }

    return 0;
}
