// PURPOSE: Registers a timer interrupt callback.

typedef unsigned int u32;

typedef struct TimerCallbackRecord {
    u32 value;
    u32 pad4;
    u32 pad8;
} TimerCallbackRecord;

extern volatile TimerCallbackRecord data_0216ff10[];
extern TimerCallbackRecord data_0216ff14[];
extern volatile TimerCallbackRecord data_0216ff18[];
extern u32 Os_EnableIrqHandler(u32 mask);

void Os_SetTimerIrqHandler(u32 timer, u32 callback, u32 argument)
{
    data_0216ff10[timer].value = callback;
    data_0216ff18[timer].value = argument;
    Os_EnableIrqHandler(1 << (timer + 3));
    data_0216ff14[timer].value = 1;
}
