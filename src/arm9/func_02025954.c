// PURPOSE: Queues three graphics transfers for a selected resource entry.
// The first argument selects one of two transfer-command ranges.
// The third argument chooses the resource entry used by the transfers.
// The exact menu graphics loaded by these transfers are uncertain.

typedef unsigned int u32;

typedef struct TeqSource {
    unsigned char unknown_00[0x10];
    void *size_10;
    unsigned char *data_14;
} TeqSource;

extern int AllocateReserveTEQSub(int command, int offset, void *source,
                                 void *size);

#pragma optimize_for_size on
void func_02025954(int alternate, TeqSource **entries, u32 index)
{
    int characterCommand;
    int paletteCommand;
    int entryOffset;

    if (alternate == 0) {
        paletteCommand = 0xf;
        switch (index) {
        case 0:
            alternate = 4;
            characterCommand = 8;
            break;
        case 1:
            alternate = 5;
            characterCommand = 9;
            break;
        case 2:
            alternate = 6;
            characterCommand = 0xa;
            break;
        case 3:
            alternate = 7;
            characterCommand = 0xb;
            break;
        }
    } else {
        paletteCommand = 0x1f;
        switch (index) {
        case 0:
            alternate = 0x14;
            characterCommand = 0x18;
            break;
        case 1:
            alternate = 0x15;
            characterCommand = 0x19;
            break;
        case 2:
            alternate = 0x16;
            characterCommand = 0x1a;
            break;
        case 3:
            alternate = 0x17;
            characterCommand = 0x1b;
            break;
        }
    }

    entryOffset = index << 2;
    AllocateReserveTEQSub(
        alternate, 0,
        ((TeqSource **)((int)entries + entryOffset))[0]->data_14,
        ((TeqSource **)((int)entries + entryOffset))[0]->size_10);
    AllocateReserveTEQSub(paletteCommand, 0, ((void ***)entries)[4][3],
                          (void *)0x140);
    AllocateReserveTEQSub(
        characterCommand, 0,
        ((TeqSource *)((unsigned char *)entries + entryOffset))->data_14 + 0xc,
        *(void **)(((TeqSource *)((unsigned char *)entries + entryOffset))
                       ->data_14 +
                   8));
}
