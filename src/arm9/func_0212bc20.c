// PURPOSE: Unlocks a sound channel and clears its channel bit from the active mask.
// The argument is a channel bit mask.
// A zero mask has no effect.

typedef unsigned int u32;

extern void SND_UnlockChannel(u32 mask, int value);
extern u32 data_0217d440;

void func_0212bc20(u32 mask)
{
    if (mask == 0) {
        return;
    }

    SND_UnlockChannel(mask, 0);
    data_0217d440 &= ~mask;
}
