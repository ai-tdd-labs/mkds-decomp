// PURPOSE: Sets the function called when the current thread switches.
// The supplied callback replaces the old callback while interrupts are disabled.
// It returns the callback that was installed before this call.

typedef unsigned int u32;
typedef void (*OsThreadSwitchCallback)(void);

typedef struct OsThreadContext {
    char padding[0xc];
    OsThreadSwitchCallback threadSwitchCallback;
} OsThreadContext;

extern OsThreadContext data_0216ff5c;
extern u32 Os_DisableIrq(void);
extern u32 Os_RestoreIrq(u32 state);

OsThreadSwitchCallback Os_SetThreadSwitchCallback(OsThreadSwitchCallback callback)
{
    u32 irqState;
    OsThreadSwitchCallback previousCallback;

    irqState = Os_DisableIrq();
    previousCallback = data_0216ff5c.threadSwitchCallback;
    data_0216ff5c.threadSwitchCallback = callback;
    Os_RestoreIrq(irqState);

    return previousCallback;
}
