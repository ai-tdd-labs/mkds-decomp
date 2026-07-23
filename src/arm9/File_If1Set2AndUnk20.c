// PURPOSE: Sets file state flags while interrupts are disabled when the file is active.

#pragma optimize_for_size on

typedef unsigned int u32;

typedef struct FileIf1Unk {
    char _00[0x1c];
    u32 unk1c;
} FileIf1Unk;

typedef struct FileIf1 {
    char _00[8];
    FileIf1Unk *unk8;
    volatile u32 flags;
} FileIf1;

extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 irqState);

void File_If1Set2AndUnk20(FileIf1 *file)
{
    u32 irqState = Os_DisableIrq();
    int enabled = ((file->flags & 1) != 0);

    if (enabled != 0) {
        file->flags |= 2;
        file->unk8->unk1c |= 0x20;
    }

    Os_RestoreIrq(irqState);
}
