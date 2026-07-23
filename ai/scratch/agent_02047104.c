// PURPOSE: Creates the shared scene state for the balloon hardware.
// The supplied heap provides the 0x40-byte state record.
// Its four low control flags and probably optional subsystem pointer are cleared.
// The balloon hardware is then initialized.

typedef unsigned int u32;

typedef struct SceneState {
    u32 unknown_00[12];
    u32 flags;
    u32 unknown_34[2];
    void *subsystem;
} SceneState;

extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void InitializeBalloonHardware(void);
extern SceneState *data_021759c4;

void CreateGlobal59C4(void *heap)
{
    data_021759c4 = (SceneState *)Mem_AllocateHeap(heap, 0x40);
    data_021759c4->flags &= ~1;
    data_021759c4->flags &= ~2;
    data_021759c4->flags &= ~4;
    data_021759c4->flags &= ~8;
    data_021759c4->subsystem = 0;
    InitializeBalloonHardware();
}
