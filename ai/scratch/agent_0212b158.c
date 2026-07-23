// PURPOSE: Creates the shared multiplayer error work area.
// The argument is the heap used for the allocation.
// It prepares the embedded sprite and initializes its state fields.

typedef struct MultiplayErrorState {
    void *sprite;
    int value0;
    int value1;
    int value2;
} MultiplayErrorState;

typedef struct MultiplayErrorWork {
    unsigned char padding_00[0x34];
    MultiplayErrorState state;
} MultiplayErrorWork;

extern void *data_0217d408;

extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void G2d_Sprite_CreateFromTiles(void *sprite, void *tiles, int mode,
                                       int option, int extra);
extern void ResetMultiplayErrors_from_thumb(void);

void InitializeGlobal1A44_from_thumb(void *heap)
{
    MultiplayErrorWork *work;
    MultiplayErrorState *state;

    work = Mem_AllocateHeap(heap, 0x1a44);
    data_0217d408 = work;
    G2d_Sprite_CreateFromTiles((unsigned char *)work + 0x14,
                               (unsigned char *)work + 0x44, 0x20, 5, 4);

    state = &((MultiplayErrorWork *)data_0217d408)->state;
    ((MultiplayErrorWork *)data_0217d408)->state.sprite =
        (unsigned char *)data_0217d408 + 0x14;
    state->value0 = 0;
    state->value1 = 1;
    state->value2 = 2;
    ResetMultiplayErrors_from_thumb();
}
