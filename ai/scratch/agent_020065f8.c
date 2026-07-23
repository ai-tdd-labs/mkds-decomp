// PURPOSE: Writes a compact command record to a buffer.
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);

u32 func_020065f8(void *destination, u16 value, u8 channel, u32 payloadValue)
{
    u8 header[4];
    u8 *cursor;

    *(u16 *)(header + 2) = value;
    header[0] = 8;
    Mem_CpuCopy8(header, destination, 1);

    cursor = (u8 *)destination + 1;
    Mem_CpuCopy8(header + 2, cursor, 2);
    cursor = (u8 *)((u32)cursor + 2);
    Mem_CpuCopy8(&channel, cursor, 1);
    cursor = (u8 *)((u32)cursor + 1);
    Mem_CpuCopy8(&payloadValue, cursor, 4);
    return (u32)(cursor + 4 - (u8 *)destination);
}
