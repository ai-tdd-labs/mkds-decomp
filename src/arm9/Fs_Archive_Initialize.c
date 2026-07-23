// PURPOSE: Initializes an archive structure to an empty state.
// The argument points to the archive structure.
// Its storage is cleared, then paired bookkeeping fields are reset.
// The exact meaning of these fields is probably archive tracking state.

typedef struct FsArchive {
    unsigned char pad000[0xc];
    int field_c;
    int field_10;
    int field_14;
    int field_18;
    unsigned char pad01c[0x5c - 0x1c];
} FsArchive;

extern void Mem_CpuFill8(void *dst, int value, int size);

void Fs_Archive_Initialize(FsArchive *archive)
{
    Mem_CpuFill8(archive, 0, 0x5c);

    archive->field_10 = 0;
    archive->field_c = archive->field_10;
    archive->field_18 = 0;
    archive->field_14 = archive->field_18;
}
