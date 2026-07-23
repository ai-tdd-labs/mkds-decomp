// PURPOSE: Emits a command for an eligible indexed record and marks it handled.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u32 func_020065a8(void *destination, u16 value, u8 flag, u32 data);

u32 func_02005d08(void *base, int index, void *destination)
{
    u32 result = 0;
    u8 *entries = (u8 *)base + 0x1D4;
    u8 *entry = entries + index * 0x68;
    u16 value = (u16)(1 << index);

    if (entries[index * 0x68] == 2 && entry[1] == 8) {
        result = func_020065a8(destination, value, entry[2], *(u32 *)(entry + 0x10));
        entry[0] = 1;
    }

    return result;
}
