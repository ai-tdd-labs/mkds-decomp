// PURPOSE: Pauses the current thread for a requested amount of time.
/*
 * The duration is converted to the OS alarm tick unit.
 * The alarm probably clears the local thread pointer when it expires.
 * Interrupt state protects the thread's temporary alarm link.
 */

typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct OsAlarm {
    unsigned char padding[0x2c];
} OsAlarm;

typedef struct OsThread {
    unsigned char padding[0xb0];
    OsAlarm *sleepAlarm;
} OsThread;

extern OsThread **data_0216ff54;
extern void Os_Alarm_Create(OsAlarm *alarm);
extern u32 Os_DisableIrq(void);
extern void Os_Alarm_Set(OsAlarm *alarm, u64 delay, void (*handler)(void), void *arg);
extern void Os_SleepAlarmHandler(void);
extern void Os_Thread_Sleep(void *queue);
extern void Os_RestoreIrq(u32 state);

void Os_Sleep(u32 duration)
{
    OsThread *thread;
    OsAlarm alarm;
    u32 state;

    Os_Alarm_Create(&alarm);
    thread = *data_0216ff54;
    state = Os_DisableIrq();
    thread->sleepAlarm = &alarm;
    Os_Alarm_Set(&alarm, (duration * 0x82ea) >> 6, Os_SleepAlarmHandler, &thread);
    while (thread != 0) {
        Os_Thread_Sleep(0);
    }
    Os_RestoreIrq(state);
}
