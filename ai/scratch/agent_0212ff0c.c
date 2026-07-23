// PURPOSE: Raises the invalid-conversion status and returns the saturated integer result.

typedef unsigned int u32;

extern u32 *GetAlphaFlagsRef(void);
extern int func_021341e0(int value, int sign, unsigned int exception);

int func_0212ff0c(int value, int sign)
{
    u32 *flags;

    flags = GetAlphaFlagsRef();
    if (*flags & 0x100) {
        return func_021341e0(value, sign, 0xe4800010);
    }
    *flags |= 1;
    return 0x7fffffff;
}
