// PURPOSE: Creates the scene subsystem when the scene is inactive.
// The heap is supplied by the caller for the subsystem allocation.
// It probably initializes the new subsystem and records its active state.

typedef struct Struct59C4Sub Struct59C4Sub;

typedef union SceneStateFlags {
    unsigned int value;
    struct {
        signed int unknown0 : 1;
        signed int active : 1;
        signed int suspended : 1;
        signed int remaining : 29;
    } bits;
} SceneStateFlags;

typedef struct SceneState {
    unsigned char padding_00[0x30];
    SceneStateFlags flags;
    unsigned char padding_34[8];
    Struct59C4Sub *subsystem;
} SceneState;

extern SceneState *data_021759c4;
extern void *Mem_AllocateHeapAligned(void *heap, unsigned int size, int alignment);
extern void Struct59C4Sub_Initialize(Struct59C4Sub *subsystem);
extern void Struct59C4Sub_SomeFn(Struct59C4Sub *subsystem);

void CreateGlobal59C4Sub(void *heap)
{
    if (data_021759c4->flags.bits.active) {
        return;
    }

    data_021759c4->subsystem = Mem_AllocateHeapAligned(heap, 0x420, 0x20);
    Struct59C4Sub_Initialize(data_021759c4->subsystem);
    Struct59C4Sub_SomeFn(data_021759c4->subsystem);
    data_021759c4->flags.value |= 2;
    data_021759c4->flags.value &= ~4;
    data_021759c4->flags.value &= ~8;
}
