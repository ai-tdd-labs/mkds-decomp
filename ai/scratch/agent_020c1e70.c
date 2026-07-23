// PURPOSE: Advances the active animation and resets its callback when the transition finishes.

typedef struct {
    char pad_00[0xa0];
    int value_a0;
    char pad_a4[8];
    void (*callback_ac)(void);
    int counter_b0;
} AnimationState;

extern AnimationState *data_0217b3e0;
extern int ComputeValueInterpolation_from_thumb(int type, int start, int end,
                                                int frame, int duration);
extern void func_020c1de4(void);

void func_020c1e70(void)
{
    int frame = data_0217b3e0->counter_b0;

    data_0217b3e0->counter_b0 = frame + 1;
    if (frame < 20) {
        data_0217b3e0->value_a0 =
            ComputeValueInterpolation_from_thumb(1, -256, 0,
                                                  frame, 20);
    } else {
        data_0217b3e0->value_a0 = 0;
        data_0217b3e0->callback_ac = func_020c1de4;
        data_0217b3e0->counter_b0 = 0;
    }
}
