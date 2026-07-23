// PURPOSE: Loads an explosion manager's wave-model availability state.

typedef struct ExplosionManagerLoadState {
    unsigned short kind;
    unsigned short padding;
    int hasNsbca;
    int hasNsbma;
} ExplosionManagerLoadState;

typedef struct ExplosionManagerInvalidState {
    int value0;
    int value4;
} ExplosionManagerInvalidState;

extern int data_0217b07c;
extern ExplosionManagerInvalidState data_0217b084;

extern void *GetExplosionSplashWaveNsbmd_from_thumb(void);
extern void *GetExplosionSplashWaveNsbca_from_thumb(void);
extern void *GetExplosionSplashWaveNsbma_from_thumb(void);

void MaybeLoadExplosionManager(ExplosionManagerLoadState *state, unsigned short kind)
{
    data_0217b07c = 0;

    if (GetExplosionSplashWaveNsbmd_from_thumb() != 0) {
        void *nsbca = GetExplosionSplashWaveNsbca_from_thumb();
        void *nsbma = GetExplosionSplashWaveNsbma_from_thumb();

        state->kind = kind;
        if (nsbca != 0) {
            state->hasNsbca = 1;
        } else {
            state->hasNsbca = 0;
        }
        if (nsbma != 0) {
            state->hasNsbma = 1;
        } else {
            state->hasNsbma = 0;
        }
    } else {
        state->kind = 0;
        state->hasNsbca = 0;
        state->hasNsbma = 0;
        data_0217b084.value0 = -1;
        data_0217b084.value4 = -1;
    }
}
