// PURPOSE: Clears one DC subrecord and marks it unused.
// The first argument is probably the base of a DC record array.
// The second argument selects a 0x100-byte subrecord.
// The selected subrecord is zeroed before its status byte is set to 0xFF.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void Mem_CpuFill16(u16 value, void *destination, u32 size);

void StructDC_CleanDCSub_from_thumb(u8 *dc, int subrecord)
{
    volatile u16 fill_value;
    u32 offset;

    fill_value = 0;
    offset = subrecord << 8;
    Mem_CpuFill16(fill_value, dc + offset, 0x100);
    *((u8 *)((int)dc + offset) + 0xE7) = 0xFF;
}
