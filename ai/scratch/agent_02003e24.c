// PURPOSE: Loads an archive's file tables into memory.
// The archive provides the FAT and FNT locations and sizes.
// The caller provides the destination buffer and its available size.
// The function returns the required aligned size even when the buffer is too small.

typedef unsigned char u8;
typedef signed int s32;
typedef unsigned int u32;

typedef struct FSFile {
    u32 words[18];
} FSFile;

typedef struct FSArchive FSArchive;
typedef int (*FSArchiveReadFunction)(FSArchive *archive, void *destination,
                                     u32 position, u32 size);

struct FSArchive {
    u8 pad_00[0x1c];
    u32 flags;
    u8 pad_20[0x0c];
    u32 fat;
    u32 fatSize;
    u32 fnt;
    u32 fntSize;
    u32 fatBackup;
    u32 fntBackup;
    void *loadMemory;
    FSArchiveReadFunction readFunction;
    void *writeFunction;
    FSArchiveReadFunction tableFunction;
};

extern void Fs_File_Initialize(FSFile *file);
extern int Fs_File_OpenRaw(FSFile *file, FSArchive *archive, u32 start,
                           u32 end, u32 fileId);
extern s32 Fs_File_Read(FSFile *file, void *destination, s32 size);
extern int Fs_File_Close(FSFile *file);
extern void Mem_CpuFill8(void *destination, u32 value, u32 size);
extern int Fs_Archive_DefaultFatFntRead(FSArchive *archive, void *destination,
                                        u32 position, u32 size);

#define ALIGN_BYTE(value, alignment) \
    (((u32)(value) + ((alignment) - 1)) & ~((alignment) - 1))

u32 Fs_Archive_LoadFatFnt(FSArchive *archive, void *memory, u32 maxSize)
{
    u32 totalSize = ALIGN_BYTE(archive->fatSize + archive->fntSize + 32, 32);

    if (totalSize <= maxSize) {
        u8 *cache = (u8 *)ALIGN_BYTE((u32)memory, 32);
        FSFile file;

        Fs_File_Initialize(&file);
        if (Fs_File_OpenRaw(&file, archive, archive->fat,
                            archive->fat + archive->fatSize, (u32)~0)) {
            if (Fs_File_Read(&file, cache, (s32)archive->fatSize) < 0) {
                Mem_CpuFill8(cache, 0, archive->fatSize);
            }
            (void)Fs_File_Close(&file);
        }
        archive->fat = (u32)cache;
        cache += archive->fatSize;

        if (Fs_File_OpenRaw(&file, archive, archive->fnt,
                            archive->fnt + archive->fntSize, (u32)~0)) {
            if (Fs_File_Read(&file, cache, (s32)archive->fntSize) < 0) {
                Mem_CpuFill8(cache, 0, archive->fntSize);
            }
            (void)Fs_File_Close(&file);
        }
        archive->fnt = (u32)cache;
        archive->loadMemory = memory;
        archive->tableFunction = Fs_Archive_DefaultFatFntRead;
        archive->flags |= 4;
    }

    return totalSize;
}
