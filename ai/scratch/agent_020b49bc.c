// PURPOSE: Finds the character graphics block in a graphics file.
// The first argument receives the block data when the file contains it.
// The second argument is probably an NCGR graphics-file buffer.

extern void *Common_FindBlockByMagic(void *file, unsigned int magic);

void Gfx_ReadCharGraphicsRelative(void **graphics, void *file)
{
    void *block;

    if (file != 0) {
        block = Common_FindBlockByMagic(file, 0x43484152);
        if (block != 0) {
            *graphics = (char *)block + 8;
        }
    }
}
