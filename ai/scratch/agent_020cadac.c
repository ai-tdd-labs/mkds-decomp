// PURPOSE: Updates a timing value and optionally plays a sound.

typedef struct WorkState {
    int value_00;
    char _04[0x1C];
    int value_20;
    int value_24;
    int value_28;
} WorkState;

extern WorkState *data_0217b438;
extern void MaybePlaySomeSseqFromSarc0(int soundId);

int func_020cadac(int soundId)
{
    int value;
    int divisor;
    WorkState *state;
    state = data_0217b438;

    value = state->value_20;
    if (state->value_00 != 0) {
        divisor = state->value_28;
        if (soundId != 0) {
            state->value_24 = 0;
            MaybePlaySomeSseqFromSarc0(0);
        }
        data_0217b438->value_20 = (divisor + (value + soundId)) % divisor;
    }
    return value;
}
