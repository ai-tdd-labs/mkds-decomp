// PURPOSE: Returns the masked tile attribute from a selected metatile entry.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u16 unknown_0;
    u16 unknown_2;
    u16 attribute;
} TileRecord;

typedef struct {
    u16 count;
    u16 unknown_2;
    TileRecord *tiles;
} MetatileEntry;

typedef struct {
    u32 unknown_0;
    u32 metatile_id;
} CellDescriptor;

extern MetatileEntry *CellBank_GetMetatileEntry(void *cell_bank, u16 index);

u16 func_0212497c(int index, void *cell_bank, CellDescriptor *descriptors)
{
    u16 attribute;

    descriptors += 1;
    index <<= 3;
    attribute = CellBank_GetMetatileEntry(
        cell_bank, (u16)*(u32 *)((u8 *)descriptors + index + 4))->tiles->attribute;
    return attribute & 0x3ff;
}
