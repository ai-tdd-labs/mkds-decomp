// PURPOSE: Finds the archive registered under a mount name.
// The mount name is packed before the archive list is searched.
// Interrupts are disabled while the shared archive list is traversed.

typedef unsigned int u32;

typedef struct FsArchive {
    u32 mountName;
    struct FsArchive *next;
} FsArchive;

extern u32 Fs_PackArchiveMountName(const char *mountName);
extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 irqState);
extern FsArchive *data_0216f340;

FsArchive *Fs_FindArchiveByMountName(const char *mountName)
{
    u32 packedMountName = Fs_PackArchiveMountName(mountName);
    u32 irqState = Os_DisableIrq();
    FsArchive *archive = data_0216f340;

    while (archive != 0 && archive->mountName != packedMountName) {
        archive = archive->next;
    }

    Os_RestoreIrq(irqState);
    return archive;
}
