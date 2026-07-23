// PURPOSE: Returns the selected cell's encoded tile attribute class.

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
    u32 unknown_0;
    u16 attribute;
} MetatileData;

extern MetatileEntry *CellBank_GetMetatileEntry(void *cell_bank, u16 id);

u8 func_021249f0(u32 index, void *cell_bank, CellDescriptor *descriptors)
{
    u16 id;
    MetatileEntry *entry;
    MetatileData *data;
    u16 attribute;

    id = (u16)(descriptors + 1)[index].metatile_id;
    entry = CellBank_GetMetatileEntry(cell_bank, id);
    data = (MetatileData *)entry->data;
    attribute = data->attribute;
    return (u8)((attribute & 0x0C00) >> 10);
}
