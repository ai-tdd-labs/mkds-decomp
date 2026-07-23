// PURPOSE: Creates an expandable heap in an aligned memory region.
/*
 * The supplied memory range is rounded to four-byte boundaries.
 * It must retain enough space for the expandable-heap header.
 */

typedef unsigned int u32;

extern void *Mem_Exp_Initialize(void *start, void *end, int option);

void *Mem_Exp_Create(void *memory, u32 size, int option)
{
    u32 start = (u32)memory + 3;
    u32 end = size + (u32)memory;

    end &= ~3;
    start &= ~3;
    if (start > end || end - start < 0x4c) {
        return 0;
    }

    return Mem_Exp_Initialize((void *)start, (void *)end, option);
}
