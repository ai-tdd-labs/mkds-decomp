// PURPOSE: Finds the screen data block and returns its contents.
// The first argument is probably a screen resource container.
// The second argument receives the block payload after its header.

extern void *Common_FindBlockByMagic(void *container, unsigned int magic);

int Screen_ReadBlock(void *container, void **out)
{
    void *block;

    block = Common_FindBlockByMagic(container, 0x5343524e);
    if (block != 0) {
        *out = (char *)block + 8;
        return 1;
    }
    *out = 0;
    return 0;
}
