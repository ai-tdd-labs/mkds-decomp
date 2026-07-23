// PURPOSE: Restores the sound heap state when its saved marker changed.
typedef unsigned int u32;

typedef struct {
    u32 word0;
    u32 word4;
    u32 word8;
} SoundSavedState;

extern SoundSavedState data_0215c380;
extern void *data_0217d130;
extern SoundSavedState data_0215c38c;

extern void Sound_MaybeRestoreHeapState(void *context, u32 state);
extern void Sound_Context_GetMaybeSavedFrameHeapStateId(void *context);

void func_0210e434(SoundSavedState *state)
{
    SoundSavedState saved;

    saved = data_0215c380;
    if (saved.word0 == state->word0 && saved.word4 == state->word4 &&
        saved.word8 == state->word8) {
        return;
    }

    Sound_MaybeRestoreHeapState(data_0217d130, ((u32 *)state)[3]);
    Sound_Context_GetMaybeSavedFrameHeapStateId(data_0217d130);
    *state = data_0215c38c;
}
