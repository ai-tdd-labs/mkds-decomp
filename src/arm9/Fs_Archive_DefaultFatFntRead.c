/*
PURPOSE: Copies archive table data into a destination buffer.
 * The archive argument is probably callback context and is not needed here.
 * Copies the requested bytes from the supplied source to the destination.
 */
typedef unsigned int u32;

extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);

int Fs_Archive_DefaultFatFntRead(void *archive, void *destination,
                                 const void *source, u32 size)
{
    Mem_CpuCopy8(source, destination, size);
    return 0;
}
