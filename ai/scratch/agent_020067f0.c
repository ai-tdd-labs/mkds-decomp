// PURPOSE: Writes a small command header and its values into a byte buffer.
// The arguments are copied in their original byte widths.
// The returned value is the number of bytes written.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void Mem_CpuCopy8(const void *source, void *destination, u32 length);

int func_020067f0(u8 *output, u16 first, u8 second, u16 third,
                  u16 fourth, u16 fifth)
{
    u8 command;
    u16 firstValue;
    u8 *cursor;

    command = 3;
    firstValue = first;

    Mem_CpuCopy8(&command, output, 1);
    cursor = output + 1;
    Mem_CpuCopy8(&firstValue, cursor, 2);
    cursor += 2;
    Mem_CpuCopy8(&second, cursor, 1);
    cursor += 1;
    Mem_CpuCopy8(&third, cursor, 2);
    cursor += 2;
    Mem_CpuCopy8(&fourth, cursor, 2);
    cursor += 2;
    Mem_CpuCopy8(&fifth, cursor, 2);
    cursor += 2;

    return cursor - output;
}
