// PURPOSE: Removes an archive from the file system's active archive list.
// The archive is unlinked only when it is currently registered.
// Interrupts are disabled while the shared list state is changed.

typedef unsigned short u16;
typedef unsigned int u32;

typedef struct FsArchive FsArchive;

struct FsArchive {
    void *archive;
    FsArchive *previous;
    FsArchive *next;
    unsigned char pad0c[0x10];
    u32 flags;
};

typedef struct FsArchiveList {
    FsArchive *head;
    u16 field4;
    u16 field6;
    void *field8;
} FsArchiveList;

extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 irqState);
extern FsArchive *data_0216f340;
extern FsArchiveList data_0216f344;

void Fs_UnregisterArchive(FsArchive *archive)
{
    u32 irqState;

    if (archive->archive == 0) {
        return;
    }

    irqState = Os_DisableIrq();

    if (archive->previous != 0) {
        archive->previous->next = archive->next;
    }
    if (archive->next != 0) {
        archive->next->previous = archive->previous;
    }

    archive->archive = 0;
    archive->previous = archive->next = 0;
    archive->flags &= ~1;

    if (data_0216f344.head == archive) {
        data_0216f344.field8 = 0;
        data_0216f344.field6 = 0;
        data_0216f344.head = data_0216f340;
        data_0216f344.field4 = 0;
    }

    Os_RestoreIrq(irqState);
}
