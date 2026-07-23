// PURPOSE: Inserts an alarm into the queue at its scheduled time.
// The alarm and its absolute fire tick are supplied by the caller.
// Periodic alarms are probably advanced to their next future occurrence.
// The queue stays ordered, and a new head immediately updates the timer.

typedef unsigned long long u64;
typedef long long s64;

typedef struct OsAlarm OsAlarm;

struct OsAlarm {
    void (*handler)(void *);
    void *arg;
    unsigned int tag;
    u64 fire;
    OsAlarm *prev;
    OsAlarm *next;
    u64 period;
    u64 start;
};

typedef struct AlarmQueue {
    OsAlarm *head;
    OsAlarm *tail;
} AlarmQueue;

extern AlarmQueue data_02170260;
extern u64 Os_GetTick(void);
extern void Os_SetAlarmTimer(OsAlarm *alarm);

void Os_InsertAlarm(OsAlarm *alarm, u64 fire)
{
    if (alarm->period > 0) {
        u64 tick = Os_GetTick();

        fire = alarm->start;
        if (alarm->start < tick) {
            fire += alarm->period * ((tick - alarm->start) / alarm->period + 1);
        }
    }

    alarm->fire = fire;

    OsAlarm *prev;
    OsAlarm *next;

    for (next = data_02170260.head; next; next = next->next) {
        if ((s64)(fire - next->fire) >= 0) {
            continue;
        }

        alarm->prev = next->prev;
        next->prev = alarm;
        alarm->next = next;
        prev = alarm->prev;
        if (prev) {
            prev->next = alarm;
        } else {
            data_02170260.head = alarm;
            Os_SetAlarmTimer(alarm);
        }

        return;
    }

    alarm->next = 0;
    prev = data_02170260.tail;
    data_02170260.tail = alarm;
    alarm->prev = prev;
    if (prev) {
        prev->next = alarm;
    } else {
        data_02170260.head = data_02170260.tail = alarm;
        Os_SetAlarmTimer(alarm);
    }
}
