// PURPOSE: Writes a type-five command record into a byte buffer.
// The record contains a halfword, a byte, and two word values.
// A final payload is copied when present, or cleared when it is absent.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);
extern void Mem_CpuFill8(void *destination, int value, u32 size);

int func_0200671c(void *buffer, u16 value, u8 flag, u32 firstValue,
                  u32 secondValue, const void *payload, u32 payloadSize)
{
    u8 header[4];
    u8 *cursor;

    *(u16 *)(header + 2) = value;
    header[0] = 5;
    Mem_CpuCopy8(header, buffer, 1);

    cursor = (u8 *)buffer + 1;
    Mem_CpuCopy8(header + 2, cursor, 2);
    cursor = (u8 *)((u32)cursor + 2);
    Mem_CpuCopy8(&flag, cursor, 1);
    cursor = (u8 *)((u32)cursor + 1);
    Mem_CpuCopy8(&firstValue, cursor, 4);
    cursor = (u8 *)((u32)cursor + 4);
    Mem_CpuCopy8(&secondValue, cursor, 4);
    cursor = (u8 *)((u32)cursor + 4);
    if (payload == 0)
        Mem_CpuFill8(cursor, 0, payloadSize);
    else
        Mem_CpuCopy8(payload, cursor, payloadSize);

    return (int)(cursor + payloadSize - (u8 *)buffer);
}
