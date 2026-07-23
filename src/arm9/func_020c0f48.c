// PURPOSE: Updates the timed value and starts its callback when it finishes.
// The shared work object probably tracks a short interpolation countdown.
// It stores each calculated value until the countdown reaches twenty frames.

typedef struct {
    unsigned char pad_00[0xa0];
    int value;
    int pad_a4;
    int pad_a8;
    void (*callback)(void);
    int counter;
} WorkState;

extern WorkState *data_0217b3e0;
extern int ComputeValueInterpolation_from_thumb(int, int, int, int, int);
extern void func_020c0f0c(void);

void func_020c0f48(void)
{
    int count = data_0217b3e0->counter;
    data_0217b3e0->counter = count + 1;
    if (count < 20) {
        data_0217b3e0->value = ComputeValueInterpolation_from_thumb(1, 128, 0, count, 20);
    } else {
        data_0217b3e0->value = 0;
        data_0217b3e0->callback = func_020c0f0c;
        data_0217b3e0->counter = 0;
    }
}
