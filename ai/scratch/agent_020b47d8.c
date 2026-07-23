// PURPOSE: Finds the screen data block in a graphics file.
// The first argument receives the block payload when it is present.
// The second argument is probably a screen graphics-file buffer.

extern void *Common_FindBlockByMagic(void *file, unsigned int magic);

void MaybeReadScreenBlock(void **screen, void *file)
{
    void *block;

    if (file != 0) {
        block = Common_FindBlockByMagic(file, 0x5343524e);
        if (block != 0) {
            *screen = (char *)block + 8;
        }
    }
}
