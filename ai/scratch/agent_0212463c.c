// PURPOSE: Copies tile graphics and palette data between two metatile entries.
// The two indices select entries from separate cell banks.
// Each tile transfer is queued for the selected display engine.
// The first tile's palette block is queued after all character data.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct TileRecord {
    u16 group;
    u16 flip;
    u16 attribute;
} TileRecord;

typedef struct MetatileEntry {
    u16 count;
    u16 unknown_2;
    TileRecord *tiles;
} MetatileEntry;

typedef struct BankSlot {
    u32 unknown_0;
    u32 metatile_id;
} BankSlot;

typedef struct CharacterDestination {
    u8 pad_00[0x14];
    u8 *base;
} CharacterDestination;

typedef struct PaletteDestination {
    u8 pad_00[0xc];
    u8 *base;
} PaletteDestination;

extern MetatileEntry *CellBank_GetMetatileEntry(void *bank, u16 id);
extern void Arm_FlushRange(void *address, u32 size);
extern void AllocateReserveTEQSub(int command, u32 offset, void *destination,
                                  u32 size);
extern u8 data_0215d024[];

void func_0212463c(int destination_index, void *destination_bank,
                   CharacterDestination *character_destination,
                   PaletteDestination *palette_destination,
                   BankSlot *destination_directory, volatile int mode,
                   int source_index, void *source_bank,
                   BankSlot *source_directory)
{
    int i;
    MetatileEntry *destination_entry;
    MetatileEntry *source_entry;
    int count;
    u8 *destination;
    u32 source_offset;
    int size;

    mode = mode;

    destination_entry = CellBank_GetMetatileEntry(
        destination_bank,
        (u16)((BankSlot *)((int)destination_directory + 8))
            [destination_index]
                .metatile_id);
    source_entry = CellBank_GetMetatileEntry(
        source_bank,
        (u16)((BankSlot *)((int)source_directory + 8))[source_index]
            .metatile_id);

    i = 0;
    count = destination_entry->count;
    if (count > 0) {
        do {
            source_offset =
                (source_entry->tiles[i].attribute & 0x3ff) << 5;
            size = data_0215d024[
                       ((((u32)destination_entry->tiles[i].flip << 16) &
                         0xc0000000) >>
                        30) +
                       (((destination_entry->tiles[i].group & 0xc000u) >> 14)
                        << 2)]
                   << 5;

            Arm_FlushRange(
                destination =
                    character_destination->base +
                    ((destination_entry->tiles[i].attribute & 0x3ff) << 5),
                size);
            if (mode == 0) {
                AllocateReserveTEQSub(0x13, source_offset, destination, size);
            } else {
                AllocateReserveTEQSub(0x23, source_offset, destination, size);
            }
            i++;
        } while (i < count);
    }

    {
        u32 palette_offset =
            ((source_entry->tiles[0].attribute & 0xf000) >> 12) << 5;
        u8 *palette_address =
            palette_destination->base +
            (((destination_entry->tiles[0].attribute & 0xf000) >> 12) << 5);

        AllocateReserveTEQSub(mode == 0 ? 0xe : 0x1e, palette_offset,
                              palette_address, 0x20);
    }
}
