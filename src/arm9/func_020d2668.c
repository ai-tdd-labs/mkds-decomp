// PURPOSE: Plays a racer effect when its entry is active.
// The entry selects an effect and may provide its own racer pointer.
// The supplied racer is used when the entry has no racer pointer.
// The exact meaning of the final two values is probably effect level and mode.

typedef struct {
    unsigned char pad00[0x24];
    int effectId;
} EffectEntry;

typedef struct {
    unsigned char pad00[0x78];
    unsigned int flags78;
    unsigned char pad7c[0x18];
    void *racer94;
    EffectEntry *effect98;
} RacerEffectState;

extern void func_02024a28(void *racer, int effectId, int value, int mode);

void func_020d2668(RacerEffectState *state, void *racer, int mode, int value)
{
    int effectId = state->effect98->effectId;

    if (effectId == -1) {
        return;
    }

    if (state->flags78 & 0x40000000) {
        return;
    }

    if (state->racer94 != 0) {
        func_02024a28(state->racer94, (unsigned short)effectId, value, mode);
        return;
    }

    func_02024a28(racer, (unsigned short)effectId, value, mode);
}
