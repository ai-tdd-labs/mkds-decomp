// PURPOSE: Updates one two-bit value in a packed table entry.
// The table address is selected from a row-sized offset and the supplied index.
// The final argument is probably a small value written into that entry.

typedef unsigned short u16;

extern int _s32_div_f(int dividend, int divisor);

void func_020adec0(void *table, int index, int row, int value)
{
    int offset = ((index + (row << 6)) / 8) << 1;
    u16 entry = *(u16 *)((char *)table + offset);
    int shift = (index % 8) << 1;

    entry &= ~(3 << shift);
    entry |= value << shift;
    *(u16 *)((char *)table + offset) = entry;
}
