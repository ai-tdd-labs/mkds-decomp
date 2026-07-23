// PURPOSE: Updates selected alpha flags and returns their prior packed state.

#pragma optimize_for_size off

extern int *GetAlphaFlagsRef(void);

int func_02133e04(int mask, int value)
{
    int *flags;
    int old;

    mask = (mask & 0x1f) | ((mask & 0x1f0000) >> 8);
    value = (value & 0x1f) | ((value & 0x1f0000) >> 8);
    old = *(flags = GetAlphaFlagsRef());
    *flags = (old & ~mask) ^ value;
    return (old & 0x1f) | ((old & 0x1f00) << 8) | 0x40000000;
}
