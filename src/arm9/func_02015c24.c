// PURPOSE: Stores the value selected from a named resource entry.
// The resource points at a dictionary and carries a 16-bit scale value.
// The entry flag probably decides whether both values are reduced by half.

typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned short u16;

typedef struct ResourceHeader {
    u8 padding_00[0x2c];
    u32 value_2c;
    u8 padding_30[4];
    u16 dictionary_offset;
} ResourceHeader;

extern void *NNS_G3dGetResDataByName(void *dictionary, const char *name);

void func_02015c24(ResourceHeader *resource, const char *name, void *output)
{
    u8 *entry;
    u32 scale;
    u32 value;

    entry = NNS_G3dGetResDataByName((u8 *)resource + resource->dictionary_offset, name);
    scale = (u16)resource->value_2c;
    value = *(u16 *)entry;
    if ((*(u16 *)(entry + 2) & 1) == 0) {
        scale = (scale << 15) >> 16;
        value = (value << 15) >> 16;
    }
    *(u32 *)((u8 *)output + 0x14) = value + scale;
}
