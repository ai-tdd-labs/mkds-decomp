// PURPOSE: Writes data from an archive into the archive's storage.
// The archive base address is stored at offset 0x28.
// The source bytes are copied to that base plus the requested position.

typedef unsigned int u32;

typedef struct FSArchive {
    unsigned char pad_00[0x28];
    void *base;
} FSArchive;

extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);

int Fs_Archive_WriteFn_Default(FSArchive *archive, const void *source,
                               u32 position, u32 size)
{
    Mem_CpuCopy8(source, (unsigned char *)archive->base + position, size);
    return 0;
}
