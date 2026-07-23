// PURPOSE: Writes a compact type-ten command record to a buffer.
// The record contains a halfword, two bytes, and nine payload bytes.
// The payload is probably an encoded message body.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);

u32 func_0200654c(void *destination, u16 value, u8 flag, void *data,
                   u8 trailingByte)
{
    u8 header[4];
    u8 *cursor;

    *(u16 *)(header + 2) = value;
    header[0] = 10;
    Mem_CpuCopy8(header, destination, 1);

    cursor = (u8 *)destination + 1;
    Mem_CpuCopy8(header + 2, cursor, 2);
    cursor = (u8 *)((u32)cursor + 2);
    Mem_CpuCopy8(&flag, cursor, 1);
    cursor = (u8 *)((u32)cursor + 1);
    Mem_CpuCopy8(&trailingByte, cursor, 1);
    cursor = (u8 *)((u32)cursor + 1);
    Mem_CpuCopy8(data, cursor, 9);

    return (u32)(cursor + 9 - (u8 *)destination);
}
