// PURPOSE: Builds an obfuscated Nintendo Wi-Fi user ID.
// The identifier supplies two 24-bit device values.
// The other arguments add a one-bit flag and a two-bit type value.
// The packed value is substituted, permuted, rotated, and limited to 43 bits.

typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;

extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);
extern const u8 data_02161730[];
extern const u8 data_02161738[];

u64 func_0215211c(u64 identifier, u32 flag, u32 kind)
{
    u64 value;
    u64 copy;
    int i;

    /* Keep the fields separate to preserve the compiler's 64-bit OR tree. */
    value = (identifier & 0xffffff) << 27;
    value = value | (((identifier >> 32) & 0xffffff) << 3);
    value = value | (((u64)flag & 1) << 2);
    value = value | ((u64)kind & 3);

    for (i = 0; i < 6; i++) {
        ((u8 *)&value)[i] ^= 0xd6;
    }

    for (i = 0; i < 5; i++) {
        u8 byte = ((u8 *)&value)[i];

        ((u8 *)&value)[i] =
            (data_02161738[(byte >> 4) & 0xf] << 4) |
            data_02161738[byte & 0xf];
    }

    Mem_CpuCopy8(&value, &copy, 8);
    for (i = 0; i < 5; i++) {
        ((u8 *)&value)[data_02161730[i]] = ((u8 *)&copy)[i];
    }

    ((u8 *)&value)[7] = 0;
    ((u8 *)&value)[6] = 0;
    ((u8 *)&value)[5] &= 7;

    value <<= 1;
    ((u8 *)&value)[0] |= (((u8 *)&value)[5] >> 3) & 1;

    for (i = 0; i < 6; i++) {
        ((u8 *)&value)[i] ^= 0x67;
    }

    ((u8 *)&value)[7] = 0;
    ((u8 *)&value)[6] = 0;
    ((u8 *)&value)[5] &= 7;

    return value;
}
