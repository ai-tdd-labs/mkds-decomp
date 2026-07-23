// PURPOSE: Finds and prepares character graphics data in a graphics file.
// The first argument receives the character graphics block when it is found.
// The second argument is probably an NCGR file buffer.
// The raw graphics range is flushed after the optional block lookup.

typedef struct {
    char padding[0x10];
    unsigned int size;
    void *rawData;
} CharGraphics;

extern void *Common_FindBlockByMagic(void *file, unsigned int magic);
extern void Gfx_MakeCharGraphicsOffsetsAbsolute(void *graphics);
extern void Arm_FlushRange(void *address, unsigned int size);

void Gfx_ReadCharGraphics(void **graphics, void *file)
{
    void *block;

    if (file != 0) {
        block = Common_FindBlockByMagic(file, 0x43484152);
        if (block != 0) {
            *graphics = (char *)block + 8;
            Gfx_MakeCharGraphicsOffsetsAbsolute(*graphics);
        }
    }

    Arm_FlushRange(((CharGraphics *)*graphics)->rawData,
                   ((CharGraphics *)*graphics)->size);
}
