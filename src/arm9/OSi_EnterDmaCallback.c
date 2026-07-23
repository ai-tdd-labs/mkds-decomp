typedef unsigned int u32;

typedef struct DmaCallbackColumn {
    u32 value;
    unsigned char padding[8];
} DmaCallbackColumn;

extern DmaCallbackColumn data_0216fee0[];
extern volatile DmaCallbackColumn data_0216fee8[];
extern DmaCallbackColumn data_0216fee4[];
extern u32 Os_EnableIrqHandler(u32 mask);

void OSi_EnterDmaCallback(u32 channel, u32 callback, u32 argument)
{
    // PURPOSE: Registers a callback for a DMA channel interrupt.
    u32 mask = 1;
    mask <<= channel + 8;
    data_0216fee0[channel].value = callback;
    *(u32 *)((int)data_0216fee8 + channel * 12) = argument;
    data_0216fee4[channel].value = Os_EnableIrqHandler(mask) & mask;
}
