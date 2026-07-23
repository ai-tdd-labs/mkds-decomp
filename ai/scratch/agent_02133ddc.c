// PURPOSE: Replaces selected alpha flags and returns their previous value.
// The arguments provide the flag mask and replacement bits.
// This changes a shared alpha-control word.

extern int *GetAlphaFlagsRef(void);

int ChangeSomeAlphaFlags(int mask, int value)
{
    int *flags;
    int old;

    old = *(flags = GetAlphaFlagsRef());
    *flags = (old & ~mask) ^ value;
    return old;
}
