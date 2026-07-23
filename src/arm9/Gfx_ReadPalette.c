// PURPOSE: Reads palette data from a graphics file.
// The output receives the palette block after its file header.
// Its raw palette bytes are made visible to the ARM cache.

typedef unsigned int u32;

typedef struct PaletteData {
    char header[8];
    u32 size;
    void *raw_data;
} PaletteData;

extern void *Common_FindBlockByMagic(void *container, unsigned int magic);
extern void Gfx_MakePaletteOffsetsAbsolute(void *palette);
extern void Arm_FlushRange(void *buffer, u32 size);

void Gfx_ReadPalette(PaletteData **output, void *buffer)
{
    void *block;

    if (buffer != 0) {
        block = Common_FindBlockByMagic(buffer, 0x504c5454);
        if (block != 0) {
            *output = (PaletteData *)((char *)block + 8);
            Gfx_MakePaletteOffsetsAbsolute(*output);
        }
    }
    Arm_FlushRange((*output)->raw_data, (*output)->size);
}
