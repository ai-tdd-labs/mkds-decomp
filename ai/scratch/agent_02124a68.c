// PURPOSE: Gets the palette index stored in a cell's metatile data.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u32 unknown_0;
    u32 metatile_id;
} CellDescriptor;

typedef struct {
    u32 unknown_0;
    void *data;
} MetatileEntry;

typedef struct {
    u16 unknown_0;
    u16 unknown_2;
    u16 attribute;
} MetatileData;

extern MetatileEntry *CellBank_GetMetatileEntry(void *cell_bank, u16 id);

u8 func_02124a68(int index, void *cell_bank, volatile CellDescriptor *descriptors)
{
    descriptors++;
    return (u8)((((MetatileData *)CellBank_GetMetatileEntry(
                    cell_bank,
                    (u16)descriptors[index].metatile_id)
                    ->data)
                    ->attribute & 0xf000) >> 12);
}
