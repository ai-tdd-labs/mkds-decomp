// PURPOSE: Clears the sound buffers and starts their hardware timers.

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

extern void MIi_CpuClear32(u32 value, void *destination, u32 size);
extern void Arm_FlushRange(void *ptr, u32 size);
extern void SND_StartTimer(u32 channelMask, u32 captureMask, u32 alarmMask,
                           u32 flags);

void func_0212cad8(void)
{
    SoundTimerState *state = &data_0217ddd0;
    volatile u32 clearValue0;
    volatile u32 clearValue1;

    if (state->initialized == 0) {
        return;
    }

    state->unknown_1c = 0;
    clearValue0 = 0;
    MIi_CpuClear32(clearValue0, state->buffer_0c, state->buffer_size_14);
    clearValue1 = 0;
    MIi_CpuClear32(clearValue1, state->buffer_10, state->buffer_size_14);
    Arm_FlushRange(state->buffer_0c, state->buffer_size_14);
    Arm_FlushRange(state->buffer_10, state->buffer_size_14);
    SND_StartTimer(state->channel_mask_24, state->capture_mask_28,
                   state->timer_bit_2c >= 0 ? 1 << state->timer_bit_2c : 0,
                   0);
}
