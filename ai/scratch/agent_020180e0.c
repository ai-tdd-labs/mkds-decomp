// PURPOSE: Creates a frame memory arena in a supplied memory range.
typedef unsigned int u32;

extern void *Mem_Frame_Initialize(void *start, void *end, int direction, u32 size);

void *Mem_Frame_Create(void *start, u32 size, int direction)
{
    u32 end = size + (u32)start;
    u32 alignedStart = (u32)start + 3;

    end &= ~3;
    alignedStart &= ~3;

    if (alignedStart > end) {
        goto fail;
    }

    size = end - alignedStart;
    if (size >= 0x30) {
        goto success;
    }

fail:
    return 0;

success:
    return Mem_Frame_Initialize((void *)alignedStart, (void *)end, direction, size);
}
