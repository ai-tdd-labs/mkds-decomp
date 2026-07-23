// PURPOSE: Queues a callback job for the global AN worker thread.
// The first argument is the queue entry to submit.
// The next two arguments are probably callbacks stored with the job.
// The priority may be absolute or relative to the worker thread.

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct OSThread {
    u8 padding[0xc0];
} OSThread;

typedef struct StructANN StructANN;

struct StructANN {
    StructANN *next;
    u32 active : 1;
    u32 priority : 31;
    void (*callback2)(StructANN *entry);
    void (*callback)(StructANN *entry);
    u32 value10;
    u32 value14;
    u32 value18;
    u32 value1c;
};

typedef struct GlobalANWork {
    OSThread thread;
    StructANN *volatile head;
    StructANN stopEntry;
} GlobalANWork;

extern int IsGlobalANSet_from_thumb(void);
extern void Os_Terminate(void);
extern int Os_Thread_GetPriority(OSThread *thread);
extern u32 Os_DisableIrq(void);
extern void Os_Thread_WakeUpDirect(OSThread *thread);
extern void Os_RestoreIrq(u32 irqState);
extern GlobalANWork *data_0216fde0;

void StructANN_SomeFn_from_thumb(StructANN *entry,
                                 void (*callback2)(StructANN *entry),
                                 void (*callback)(StructANN *entry),
                                 u32 priority)
{
    GlobalANWork *work = data_0216fde0;
    u32 irqState;

    if (IsGlobalANSet_from_thumb() == 0) {
        Os_Terminate();
    }
    if (entry->active != 0) {
        Os_Terminate();
    }

    if (priority > 31) {
        u32 threadPriority = Os_Thread_GetPriority(&work->thread);

        if (priority == 32) {
            if (threadPriority != 0) {
                priority = threadPriority - 1;
            } else {
                priority = 0;
            }
        } else if (priority == 33) {
            if (threadPriority < 31) {
                priority = threadPriority + 1;
            } else {
                priority = 31;
            }
        } else if (priority == 34) {
            priority = threadPriority;
        } else {
            priority = 31;
        }
    }

    irqState = Os_DisableIrq();
    entry->active = 1;
    entry->priority = priority;
    entry->callback2 = callback2;
    entry->callback = callback;

    if (work->head == 0) {
        if (entry == &work->stopEntry) {
            data_0216fde0 = 0;
        }
        work->head = entry;
        Os_Thread_WakeUpDirect(&work->thread);
    } else {
        StructANN *current = work->head;

        if (entry == &work->stopEntry) {
            while (current->next != 0) {
                current = current->next;
            }
            current->next = entry;
            data_0216fde0 = 0;
        } else if (current->priority > priority) {
            work->head = entry;
            entry->next = current;
        } else {
            while (current->next != 0 &&
                   current->next->priority <= priority) {
                current = current->next;
            }
            entry->next = current->next;
            current->next = entry;
        }
    }

    Os_RestoreIrq(irqState);
}
