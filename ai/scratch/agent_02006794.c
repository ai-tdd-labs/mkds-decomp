// PURPOSE: Copies a compact record into its argument storage.
// The source probably contains a one-byte tag, a halfword, and three values.
// It returns the number of source bytes consumed.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct RecordHeader {
    u8 tag;
    u8 pad;
    u16 value;
} RecordHeader;

extern void Mem_CpuCopy8(void *dst, const void *src, u32 size);

int func_02006794(void *source, u16 value, u8 third, u32 fourth, u32 fifth)
{
    RecordHeader header;
    u8 *cursor;

    header.value = value;
    header.tag = 4;

    Mem_CpuCopy8(&header, source, 1);
    cursor = (u8 *)source + 1;
    Mem_CpuCopy8(&header.value, cursor, 2);
    cursor = (u8 *)((u32)cursor + 2u);
    Mem_CpuCopy8(&third, cursor, 1);
    cursor = (u8 *)((u32)cursor + 1u);
    Mem_CpuCopy8(&fourth, cursor, 4);
    cursor = (u8 *)((u32)cursor + 4u);
    Mem_CpuCopy8(&fifth, cursor, 4);

    return (int)(cursor + 4 - (u8 *)source);
}
