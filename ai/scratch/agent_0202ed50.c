// PURPOSE: Applies a palette bank to the right edge of a tile map.
// The argument selects the four-bit palette bank for the affected tiles.
// Four columns in each of eighteen rows are updated, then the full map is
// probably queued for transfer to video memory.

typedef unsigned char u8;
typedef unsigned short u16;

#pragma optimize_for_size on

extern u8 *data_02174e48;
extern void AllocateReserveTEQSub(int command, int offset, void *source,
                                  int size);

void func_0202ed50(int palette)
{
    int row;
    int column;

    for (row = 1; row < 0x13; row++) {
        for (column = 0x1c; column < 0x20; column++) {
            /* Keep the row and column combined before scaling to bytes. */
            *(u16 *)(data_02174e48
                     + ((((unsigned int)row << 5) + column) << 1)
                     + 0x58) &= 0x0fff;
            *(u16 *)(data_02174e48
                     + ((((unsigned int)row << 5) + column) << 1)
                     + 0x58) |= palette << 12;
        }
    }

    *(int *)(data_02174e48 + 0x65c) = 5;
    *(int *)(data_02174e48 + 0x658) = palette;
    AllocateReserveTEQSub(0x1b, 0, data_02174e48 + 0x58, 0x600);
}
