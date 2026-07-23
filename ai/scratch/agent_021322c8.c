// PURPOSE: Converts a single-precision floating-point bit pattern to a signed integer.

typedef unsigned int u32;
typedef int s32;

extern u32 *GetAlphaFlagsRef(void);
extern s32 func_02132364(u32 value);

s32 func_021322c8(u32 value)
{
    u32 bits;
    s32 shift;
    u32 result;
    u32 *flags;

    bits = value & ~0x80000000;
    shift = 0x9e - (bits >> 23);
    if (shift <= 0) {
        return func_02132364(value);
    }

    if (shift >= 0x20) {
        if (bits == 0) {
            return bits;
        }
        result = 0;
    } else {
        bits = (bits << 8) | 0x80000000;
        result = bits >> shift;
        if ((s32)value < 0) {
            result = -result;
        }
        shift = 0x20 - shift;
        if ((bits << shift) == 0) {
            return result;
        }
    }

    flags = GetAlphaFlagsRef();
    if ((*flags & 0x1000) == 0) {
        *flags |= 0x10;
    }
    return result;
}
