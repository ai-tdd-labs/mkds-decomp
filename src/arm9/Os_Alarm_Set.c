// PURPOSE: Sets an alarm to run after a given number of ticks.
// The alarm must be valid and inactive before it is set.
// It records a callback and argument, then inserts the alarm with interrupts disabled.

typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct OsAlarm {
    void (*callback)(void);
    void *arg;
    char _08[0x14];
    int _1c;
    int _20;
} OsAlarm;

extern void Os_Terminate(void);
extern u32 Os_DisableIrq(void);
extern u64 Os_GetTick(void);
extern void Os_InsertAlarm(OsAlarm *alarm, u64 tick);
extern void Os_RestoreIrq(u32 irqState);

void Os_Alarm_Set(OsAlarm *alarm, u64 delay, void (*callback)(void), void *arg)
{
    u32 irqState;

    if (alarm == 0 || alarm->callback != 0) {
        Os_Terminate();
    }

    irqState = Os_DisableIrq();
    alarm->_1c = 0;
    alarm->_20 = 0;
    alarm->callback = callback;
    alarm->arg = arg;
    Os_InsertAlarm(alarm, delay + Os_GetTick());
    Os_RestoreIrq(irqState);
}
