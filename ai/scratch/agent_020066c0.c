// PURPOSE: Writes a small binary record to the buffer.
// The arguments provide the record's halfword, byte, and two word fields.
// The return value is the total number of bytes written.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);

int func_020066c0(void *buffer, u16 value, u8 flag, u32 data, u32 extra)
{
    u8 header[4];
    u8 *cursor;

    *(u16 *)(header + 2) = value;
    header[0] = 6;
    Mem_CpuCopy8(header, buffer, 1);

    cursor = (u8 *)buffer + 1;
    Mem_CpuCopy8(header + 2, cursor, 2);
    cursor = (u8 *)((u32)cursor + 2);
    Mem_CpuCopy8(&flag, cursor, 1);
    cursor = (u8 *)((u32)cursor + 1);
    Mem_CpuCopy8(&data, cursor, 4);
    cursor = (u8 *)((u32)cursor + 4);
    Mem_CpuCopy8(&extra, cursor, 4);

    return (int)(cursor + 4 - (u8 *)buffer);
}
