// PURPOSE: Reads character graphics from a graphics file.
// The first argument receives the character graphics block.
// The second argument is probably an NCGR graphics-file buffer.
// The graphics data is made absolute and its cache range is flushed.

typedef struct {
    char padding[0x10];
    unsigned int szByte;
    void *pRawData;
} CharGraphics;

extern void *Common_FindBlockByMagic(void *file, unsigned int magic);
extern void Gfx_MakeCharGraphicsOffsetsAbsoluteV2(CharGraphics *graphics);
extern void Arm_FlushRange(void *data, unsigned int size);

void Gfx_ReadCharGraphicsV2(CharGraphics **graphics, void *file)
{
    void *block;

    if (file != 0) {
        block = Common_FindBlockByMagic(file, 0x43484152);
        if (block != 0) {
            *graphics = (CharGraphics *)((char *)block + 8);
            Gfx_MakeCharGraphicsOffsetsAbsoluteV2(*graphics);
        }
    }

    Arm_FlushRange((*graphics)->pRawData, (*graphics)->szByte);
}
