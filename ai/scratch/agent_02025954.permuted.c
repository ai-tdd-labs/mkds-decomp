// PURPOSE: Queues three graphics transfers for a selected resource entry.
// The first argument selects one of two transfer-command ranges.
// The third argument selects the resource entry used by all three transfers.
// The resource layout and exact graphics purpose are probably screen-related.

typedef unsigned int u32;

typedef struct TeqSource {
    unsigned char unknown_00[0x10];
    void *unknown_10;
    unsigned char *unknown_14;
} TeqSource;

extern int AllocateReserveTEQSub(int command, u32 offset, void *destination,
                                 u32 size);

#pragma optimize_for_size on
void func_02025954(int alternate, TeqSource **entries, u32 index)
{
    int thirdCommand;
    int middleCommand;
    int entryOffset;

    if (alternate == 0) {
        middleCommand = 0xf;
        switch (index) {
        case 0:
            alternate = 4;
            thirdCommand = 8;
            break;
        case 1:
            alternate = 5;
            thirdCommand = 9;
            break;
        case 2:
            alternate = 6;
            thirdCommand = 0xa;
            break;
        case 3:
            alternate = 7;
            thirdCommand = 0xb;
            break;
        }
    } else {
        middleCommand = 0x1f;
        switch (index) {
        case 0:
            alternate = 0x14;
            thirdCommand = 0x18;
            break;
        case 1:
            alternate = 0x15;
            thirdCommand = 0x19;
            break;
        case 2:
            alternate = 0x16;
            thirdCommand = 0x1a;
            break;
        case 3:
            alternate = 0x17;
            thirdCommand = 0x1b;
            break;
        }
    }

    entryOffset = index << 2;
    AllocateReserveTEQSub(
        alternate, 0,
        ((TeqSource **)((int)entries + entryOffset))[0]->unknown_14,
        (u32)((TeqSource **)((int)entries + entryOffset))[0]->unknown_10);
    AllocateReserveTEQSub(
        middleCommand, 0, ((void ***)entries)[4][3],
        (u32)(volatile void *)0x04098909);
    AllocateReserveTEQSub(
        thirdCommand, 0,
        ((TeqSource *)((unsigned char *)entries + entryOffset))->unknown_14 + 0xc,
        *(u32 *)(((TeqSource *)((unsigned char *)entries + entryOffset))
                     ->unknown_14 +
                 8));
}
