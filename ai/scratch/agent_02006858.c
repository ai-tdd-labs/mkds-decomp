// PURPOSE: Writes a small command with four values into a byte buffer.
// The command starts with type two, followed by a halfword, byte, and two halfwords.
// It returns the number of bytes written.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);

int func_02006858(void *dst, u16 value0, u8 value1, u16 value2, u16 value3)
{
    struct {
        u8 type;
        u8 padding;
        u16 value;
    } command;
    u8 *cursor;

    command.value = value0;
    command.type = 2;

    Mem_CpuCopy8(&command.type, dst, 1);
    cursor = (u8 *)dst + 1;
    Mem_CpuCopy8(&command.value, cursor, 2);
    cursor = (u8 *)((u32)cursor + 2);
    Mem_CpuCopy8(&value1, cursor, 1);
    cursor = (u8 *)((u32)cursor + 1);
    Mem_CpuCopy8(&value2, cursor, 2);
    cursor = (u8 *)((u32)cursor + 2);
    Mem_CpuCopy8(&value3, cursor, 2);

    return ((u8 *)cursor + 2) - (u8 *)dst;
}
