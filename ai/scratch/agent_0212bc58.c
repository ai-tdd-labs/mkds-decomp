// PURPOSE: Locks an available sound channel mask.
// The mask is ignored when zero or when any requested channel is already active.
// On success it locks the channels and records their bits in the active mask.

typedef unsigned int u32;

extern void SND_LockChannel(u32 mask, int value);
extern u32 data_0217d440;

int func_0212bc58(u32 mask)
{
    if (mask == 0)
        return 1;

    if (mask & data_0217d440)
        return 0;

    SND_LockChannel(mask, 0);
    data_0217d440 |= mask;
    return 1;
}
