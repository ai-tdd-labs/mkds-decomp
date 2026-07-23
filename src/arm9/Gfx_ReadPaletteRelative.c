// PURPOSE: Finds the palette data inside a graphics file.
// The first argument receives the palette block when it is found.
// The second argument is probably an NCLR graphics-file buffer.

extern void *Common_FindBlockByMagic(void *container, unsigned int magic);

void Gfx_ReadPaletteRelative(void **output, void *buffer)
{
    void *block;

    if (buffer != 0) {
        block = Common_FindBlockByMagic(buffer, 0x504c5454);
        if (block != 0) {
            *output = (char *)block + 8; // Skip the block header.
        }
    }
}
