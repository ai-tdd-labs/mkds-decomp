// PURPOSE: Updates the selected display mode's tile attributes and schedules their transfer.

typedef unsigned short u16;

extern char *data_0217d3f8;
extern volatile u16 data_027ffc40;
extern void AllocateReserveTEQSub(int command, int offset, void *source, int size);

void func_02128624(int mode)
{
    int mask = 0xc000;
    int count = 0x260;
    int offset = 0x4c0;

    if (mode == 0) {
        mask = 0xd000;
    }

    do {
        *(u16 *)(data_0217d3f8 + offset + 0x10) &= ~0xf000;
        *(u16 *)(data_0217d3f8 + offset + 0x10) |= mask;
        offset += 2;
        count += 1;
    } while (count < 0x360);

    if (data_027ffc40 != 2) {
        AllocateReserveTEQSub(0x1a, 0x4c0, data_0217d3f8 + 0x4d0, 0x200);
    }
}
