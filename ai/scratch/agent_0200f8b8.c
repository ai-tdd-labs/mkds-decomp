// PURPOSE: Cancels an active alarm and updates the alarm queue safely.
typedef unsigned int u32;

typedef struct OsAlarm {
    void (*callback)(void);
    void *arg;
    char _08[0x0c];
    struct OsAlarm *previous;
    struct OsAlarm *next;
    int _1c;
    int _20;
} OsAlarm;

extern OsAlarm *data_02170260[];
extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 irqState);
extern void Os_SetAlarmTimer(struct OsAlarm *alarm);

void Os_Alarm_Cancel(OsAlarm *alarm)
{
    u32 irqState;
    OsAlarm *next;

    irqState = Os_DisableIrq();
    if (alarm->callback == 0) {
        Os_RestoreIrq(irqState);
        return;
    }

    next = alarm->next;
    if (next == 0) {
        data_02170260[1] = alarm->previous;
    } else {
        next->previous = alarm->previous;
    }

    if (alarm->previous != 0) {
        alarm->previous->next = next;
    } else {
        data_02170260[0] = next;
        if (next != 0) {
            Os_SetAlarmTimer(next);
        }
    }

    alarm->callback = 0;
    alarm->_1c = 0;
    alarm->_20 = 0;
    Os_RestoreIrq(irqState);
}
