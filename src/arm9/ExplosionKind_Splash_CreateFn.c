// PURPOSE: Resets the splash effect animations when the effect is created.
// The effect probably owns two animation objects at offsets 0x90 and 0x94.
// It stores the first animation's scaled current length at offset 0xAC.

extern unsigned int Animation_GetCurrentLength(void *animation);
extern void Animation_SetAt(void *animation, int slot);

typedef struct {
    char pad_0x00[0x90];
    void *animation_0x90;
    void *animation_0x94;
    char pad_0x98[0xAC - 0x98];
    int scaled_length_0xAC;
} ExplosionKindSplash;

void ExplosionKind_Splash_CreateFn(ExplosionKindSplash *effect)
{
    int scaled_length;

    scaled_length = (Animation_GetCurrentLength(effect->animation_0x90) << 4) >> 16;
    Animation_SetAt(effect->animation_0x90, 0);
    effect->scaled_length_0xAC = scaled_length;
    if (effect->animation_0x94 == 0) {
        return;
    }
    Animation_SetAt(effect->animation_0x94, 0);
}
