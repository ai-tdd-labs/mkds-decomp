// PURPOSE: Finds and stores the payload of a CEBK block.
// The first argument receives the block payload when it is found.
// The second argument is probably a container of tagged data blocks.

extern void *Common_FindBlockByMagic(void *container, unsigned int magic);

void func_020b48b4(void **payload, void *container)
{
    void *block;

    if (container != 0) {
        block = Common_FindBlockByMagic(container, 0x4345424b);
        if (block != 0) {
            *payload = (char *)block + 8;
        }
    }
}
