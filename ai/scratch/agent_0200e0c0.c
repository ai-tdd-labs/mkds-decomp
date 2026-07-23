// PURPOSE: Cancels the alarm used while a thread is sleeping.
typedef struct OsAlarm OsAlarm;

typedef struct OsThread {
    unsigned char pad_0x00[0xb0];
    OsAlarm *sleepAlarm;
} OsThread;

extern void Os_Alarm_Cancel(OsAlarm *alarm);

void Os_Thread_CancelAlarmForSleep(OsThread *thread)
{
    if (thread->sleepAlarm != 0) {
        Os_Alarm_Cancel(thread->sleepAlarm);
    }
}
