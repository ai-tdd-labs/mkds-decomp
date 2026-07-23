// PURPOSE: Finds a screen block and flushes its graphics data.
// The output receives the screen block found in the optional file buffer.
// Its raw data is then made visible to the ARM cache.

typedef unsigned int u32;

typedef struct ScreenBlock {
    char header[8];
    u32 size;
    void *rawData;
} ScreenBlock;

extern void *Common_FindBlockByMagic(void *container, unsigned int magic);
extern int Screen_ReadBlock(void *container, void **out);
extern void Arm_FlushRange(void *ptr, u32 size);

void MaybeReadScreenBlock_0(ScreenBlock **output, void *buffer)
{
    void *block;

    if (buffer != 0) {
        block = Common_FindBlockByMagic(buffer, 0x4e534352);
        if (block != 0) {
            *output = (ScreenBlock *)((char *)block + 8);
            Screen_ReadBlock(buffer, (void **)output);
        }
    }

    Arm_FlushRange((*output)->rawData, (*output)->size);
}
