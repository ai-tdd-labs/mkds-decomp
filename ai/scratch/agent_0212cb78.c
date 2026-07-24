// PURPOSE: Stops the active sound timers and waits for their commands to finish.
// Takes no arguments and returns immediately when the timer state is inactive.
// It stops every configured timer, flushes pending sound commands, and waits
// for the command list that was current before the flush.

typedef unsigned int u32;
typedef int s32;

typedef struct {
    void *initialized;
    u32 unknown_04;
    u32 unknown_08;
    void *buffer_0c;
    void *buffer_10;
    u32 buffer_size_14;
    u32 unknown_18;
    u32 unknown_1c;
    u32 unknown_20;
    u32 channel_mask_24;
    u32 capture_mask_28;
    s32 timer_bit_2c;
} SoundTimerState;

extern SoundTimerState data_0217ddd0;

extern void SND_StopTimer(u32 channelMask, u32 captureMask, u32 alarmMask,
                          u32 flags);
extern int func_02021114(void);
extern void Sound_FlushCommand(int flags);
extern void func_02021154(u32 tick);

void func_0212cb78(void)
{
    SoundTimerState *state = &data_0217ddd0;
    int tick;

    if (state->initialized == 0) {
        return;
    }

    SND_StopTimer(state->channel_mask_24, state->capture_mask_28,
                  state->timer_bit_2c >= 0 ? 1 << state->timer_bit_2c : 0,
                  0);
    tick = func_02021114();
    Sound_FlushCommand(1);
    func_02021154(tick);
}
