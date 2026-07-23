// PURPOSE: Applies a palette index to every tile in a metatile entry.
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u32 unknown0;
    u32 metatile_id;
} CellRecord;

typedef struct {
    u16 unknown0;
    u16 unknown2;
    u16 attributes;
} MetatileData;

typedef struct {
    u16 count;
    u16 unknown;
    MetatileData *data;
} MetatileEntry;

extern MetatileEntry *CellBank_GetMetatileEntry(void *bank, u16 id);

void func_02124a20(int index, int palette, void *bank, CellRecord *records)
{
    MetatileEntry *entry;
    MetatileData *data;
    int i;

    records += 1;
    index <<= 3;
    entry = CellBank_GetMetatileEntry(bank,
        (u16)*(u32 *)((u8 *)records + index + 4));
    data = entry->data;
    i = 0;
    if (i < entry->count) {
        do {
            data->attributes &= 0x0fff;
            data->attributes |= palette << 12;
            data++;
            i++;
        } while (i < entry->count);
    }
}
