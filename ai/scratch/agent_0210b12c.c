// PURPOSE: Enables two effect flags after the sound gate opens.
// The first argument is probably a racer entry and the second provides an effect ID base.
// Nothing happens until the global gate reaches 120 or effect creation fails.

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct {
    u32 gateValue;
    u8 pad04[0x15];
    volatile u8 flags19;
} RacerEffect;

typedef struct {
    u32 gateValue;
    u8 pad04[8];
    int stateC;
    u8 pad10[7];
    u8 flag17;
} SndSceneState_0217c814;

extern SndSceneState_0217c814 data_0217c814;
extern RacerEffect *StructMQRacerEntry_SomeFn_6(
    void *racer, int unused, int effectId, int level, int trailingArg);

void func_0210b12c(void *racer, int effectIdBase)
{
    RacerEffect *effect;

    if (data_0217c814.gateValue < 120) {
        return;
    }

    effect = StructMQRacerEntry_SomeFn_6(
        racer, 0, effectIdBase + 0xc1, 0x7f, 0);
    if (effect == 0) {
        return;
    }

    /* Keep these as separate hardware-visible flag updates. */
    effect->flags19 |= 0x20;
    effect->flags19 |= 0x40;
}
