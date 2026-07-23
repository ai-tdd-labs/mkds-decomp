// PURPOSE: Copies requested data into a destination buffer.
/*
 * The first argument is probably unused callback context.
 * The source and byte count are passed through to the memory-copy routine.
 */
typedef unsigned int u32;

extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);

int UnkStruct_ReadFn_RomUnk_0(void *context, void *destination,
                              const void *source, u32 size)
{
    Mem_CpuCopy8(source, destination, size);
    return 0;
}
