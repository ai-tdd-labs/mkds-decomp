/*
PURPOSE: Copies requested archive data into a destination buffer.
 * The archive probably holds the base address of its loaded data at offset 0x28.
 * It copies size bytes starting at the supplied offset, then reports success.
 */
typedef unsigned int u32;

typedef struct FsArchive {
    unsigned char padding[0x28];
    const void *data;
} FsArchive;

extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);

int Fs_Archive_ReadFn_Default(FsArchive *archive, void *destination,
                              u32 offset, u32 size)
{
    Mem_CpuCopy8((const unsigned char *)archive->data + offset, destination, size);
    return 0;
}
