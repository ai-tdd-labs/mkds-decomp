// PURPOSE: Updates a timed state transition.
// The shared state probably selects a handler after twenty updates.
// Before that point, it stores an interpolated value for the transition.

typedef struct {
    void (*handler)(void);
    int count;
    char padding_08[0xd8];
    int value;
} StructE8State;

extern StructE8State *data_0217b3f4;
extern int ComputeValueInterpolation_from_thumb(int, int, int, int, int);
extern void StructE8_SomeFnHandle6(void);

void StructE8_SomeFnHandle2(void)
{
    int count = data_0217b3f4->count;

    data_0217b3f4->count = count + 1;
    if (count < 20) {
        data_0217b3f4->value =
            ComputeValueInterpolation_from_thumb(1, -256, 0, count, 20);
    } else {
        data_0217b3f4->value = 0;
        data_0217b3f4->handler = StructE8_SomeFnHandle6;
        data_0217b3f4->count = 0;
    }
}
