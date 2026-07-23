// PURPOSE: Updates an active sound player's interpolation target.

typedef struct InterpolationState InterpolationState;

typedef struct SoundPlayer {
    unsigned char pad_00[0x1c];
    InterpolationState *interpolation;
    unsigned char pad_20[0x0c];
    unsigned char state;
} SoundPlayer;

extern void func_0212f834(InterpolationState *state, int end, int count);

void func_0212c620(SoundPlayer **handle, int value, int count)
{
    if (*handle == 0) {
        return;
    }

    if ((*handle)->state == 2) {
        return;
    }

    func_0212f834((*handle)->interpolation, value << 8, count);
}
