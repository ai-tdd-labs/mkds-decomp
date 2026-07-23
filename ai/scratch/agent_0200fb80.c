// PURPOSE: Programs timer 1 for the next pending alarm.
// The alarm provides the absolute tick when its callback should run.
// Overdue alarms use the shortest delay, while distant alarms are checked later.

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned long long u64;
typedef long long s64;

typedef struct OsAlarm {
    char _00[0xc];
    u64 tick;
} OsAlarm;

extern u64 Os_GetTick(void);
extern void Os_SetTimerIrqHandler(u32 timer, u32 callback, u32 argument);
extern void Os_AlarmHandler(void);
extern u32 Os_EnableIrqHandler(u32 mask);

void Os_SetAlarmTimer(OsAlarm *alarm)
{
    u64 now;
    s64 remaining;
    u16 reload;

    now = Os_GetTick();
    *(volatile u16 *)0x04000106 = 0;
    remaining = alarm->tick - now;
    Os_SetTimerIrqHandler(1, (u32)Os_AlarmHandler, 0);

    reload = 0;
    if (remaining < 0) {
        reload = 0xfffe;
    } else if (remaining < 0x10000) {
        reload = (u16)~remaining;
    }

    *(volatile u16 *)0x04000104 = reload;
    *(volatile u16 *)0x04000106 = 0xc1;
    Os_EnableIrqHandler(0x10);
}
