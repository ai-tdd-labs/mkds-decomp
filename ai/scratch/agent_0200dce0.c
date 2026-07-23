// PURPOSE: Changes a thread's scheduling priority and re-inserts it into the ready list.

typedef unsigned int u32;

typedef struct OsThread {
    char pad0[0x68];
    struct OsThread *next;   /* 0x68 */
    char pad6c[0x4];
    u32 priority;            /* 0x70 */
} OsThread;

typedef struct {
    char pad0[0x8];
    OsThread *readyListHead; /* 0x8 */
} OsSchedInfo;

extern OsSchedInfo data_0216ff5c;
extern OsThread data_0216ff6c;

extern u32 Os_DisableIrq(void);
extern u32 Os_RestoreIrq(u32 state);
extern void Os_InsertThread(OsThread *thread);
extern void Os_RescheduleThread(void);

int Os_Thread_SetPriority(OsThread *thread, u32 priority)
{
    OsThread *t;
    OsThread *prev;
    u32 irq;

    t = data_0216ff5c.readyListHead;
    prev = 0;
    irq = Os_DisableIrq();

    while (t != 0 && t != thread) {
        prev = t;
        t = t->next;
    }

    if (t == 0 || t == &data_0216ff6c) {
        Os_RestoreIrq(irq);
        return 0;
    }

    if (t->priority != priority) {
        if (prev == 0) {
            data_0216ff5c.readyListHead = thread->next;
        } else {
            prev->next = thread->next;
        }
        thread->priority = priority;
        Os_InsertThread(thread);
        Os_RescheduleThread();
    }

    Os_RestoreIrq(irq);
    return 1;
}
