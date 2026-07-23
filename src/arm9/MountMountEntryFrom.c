// PURPOSE: Mounts a NARC archive from a memory buffer.
// The entry receives the archive state, mount name, and raw NARC pointer.
// It finds the FAT, filename, and file-image blocks before registering the archive.
// It returns one on success and unregisters a partially mounted archive on failure.

typedef unsigned int u32;

typedef struct MountArchiveEntry {
    unsigned char archive[0x5c];
    void *narc_raw_ptr;
    void *fat_block_ptr;
    void *fimg_data_start;
} MountArchiveEntry;

extern int ArcEntry_ValidateNarcHeader(void *narc_ptr);
extern void Fs_Archive_Initialize(void *archive);
extern u32 strlen(const char *string);
extern int Fs_RegisterArchive(void *archive, char *mount_name, u32 name_length);
extern int Fs_Archive_LoadFromFatFnt(void *archive, int base, int fat,
                                    int fat_size, int fnt, int fnt_size,
                                    void *read_func, void *write_func);
extern void Fs_UnregisterArchive(void *archive);

int MountMountEntryFrom(MountArchiveEntry *entry, char *mount_name,
                        char *narc_ptr)
{
    char *fat_block;
    char *fnt_block;
    char *fimg_block;
    int i;
    char *block;
    int block_count;
    char *fimg_data;

    fat_block = 0;
    fnt_block = 0;
    fimg_block = 0;

    if (ArcEntry_ValidateNarcHeader(narc_ptr) == 0)
        return 0;

    block = narc_ptr + *(unsigned short *)(narc_ptr + 0xc);
    block_count = *(unsigned short *)(narc_ptr + 0xe);
    i = 0;
    if (block_count > 0) {
        do {
            unsigned int magic = *(unsigned int *)block;

            switch (magic) {
            case 0x46415442: /* BTAF */
                fat_block = block;
                break;
            case 0x464e5442: /* BTNF */
                fnt_block = block;
                break;
            case 0x46494d47: /* GMIF */
                fimg_block = block;
                break;
            }

            block += *(int *)(block + 4);
            i++;
        } while (i < block_count);
    }

    Fs_Archive_Initialize(entry);
    entry->narc_raw_ptr = narc_ptr;
    entry->fat_block_ptr = fat_block;
    fimg_data = fimg_block + 8;
    entry->fimg_data_start = fimg_data;

    if (Fs_RegisterArchive(entry, mount_name, strlen(mount_name)) == 0)
        return 0;

    if (Fs_Archive_LoadFromFatFnt(
            entry, (int)fimg_data,
            (int)(fat_block + 0xc) - (int)fimg_data,
            *(int *)(fat_block + 4) - 0xc,
            (int)(fnt_block + 8) - (int)fimg_data,
            *(int *)(fnt_block + 4) - 8, 0, 0))
        return 1;

    Fs_UnregisterArchive(entry);
    return 0;
}
