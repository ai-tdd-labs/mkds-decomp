// PURPOSE: Starts the main scheduler thread and its idle thread.
// This function takes no arguments and does nothing after its first call.
// It records the currently running thread, installs stack guards, and exposes
// the scheduler state before creating the lowest-priority idle thread.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct OsThread OsThread;

typedef struct OsThreadQueue {
    OsThread *head;
    OsThread *tail;
} OsThreadQueue;

typedef struct OsThreadLink {
    OsThread *previous;
    OsThread *next;
} OsThreadLink;

struct OsThread {
    u8 context[0x64];
    int state;
    OsThread *next;
    u32 id;
    u32 priority;
    void *profiler;
    OsThreadQueue *queue;
    OsThreadLink link;
    void *mutex;
    OsThreadQueue mutexQueue;
    u32 stackTop;
    u32 stackBottom;
    u32 stackWarningOffset;
    OsThreadQueue joinQueue;
    void *specific[3];
    void *alarmForSleep;
    void (*destructor)(void *);
    void *userParameter;
    u32 systemErrno;
};

typedef void (*OsThreadSwitchCallback)(OsThread *from, OsThread *to);

typedef struct OsThreadInfo {
    u16 needsRescheduling;
    u16 irqDepth;
    OsThread *current;
    OsThread *list;
    OsThreadSwitchCallback threadSwitchCallback;
} OsThreadInfo;

extern OsThread **data_0216ff54;
extern int data_0216ff58;
extern OsThreadInfo data_0216ff5c;
extern OsThread *data_0216ff60;
extern OsThread data_0216ff6c;
extern OsThread data_0217002c;
extern u32 data_021701b4;

extern void Os_IdleThreadMain(void *argument);
extern OsThreadSwitchCallback
Os_SetThreadSwitchCallback(OsThreadSwitchCallback callback);
extern void Os_Thread_Create(OsThread *thread, void (*entry)(void *),
                             void *argument, void *stackTop, u32 stackSize,
                             u32 priority);

/* Function-pointer literals preserve the SDK's absolute stack-size words. */
#define SYSTEM_STACK_SIZE ((s32)(void (*)(void))0x00002800)
#define IRQ_STACK_SIZE ((s32)(void (*)(void))0x00000c00)
#define DTCM_BASE ((u32)(volatile u8 *)0x027e0000)
#define DTCM_ARENA_START ((u32)(volatile u8 *)0x027e00e0)
#define DTCM_SYSTEM_STACK (DTCM_BASE + 0x3f80)

static inline void Os_SetCurrentThread(OsThread *thread)
{
    data_0216ff5c.current = thread;
}

static inline void Os_InitializeThreadQueue(OsThreadQueue *queue)
{
    queue->head = queue->tail = 0;
}

void Os_InitializeThread(void)
{
    if (data_0216ff58)
        return;
    data_0216ff58 = 1;

    data_0216ff54 = &data_0216ff60;

    data_0217002c.priority = 0x10;
    data_0217002c.id = 0;
    data_0217002c.state = 1;
    data_0217002c.next = 0;
    data_0217002c.profiler = 0;

    data_0216ff5c.list = &data_0217002c;
    Os_SetCurrentThread(&data_0217002c);

    void *stackLow = SYSTEM_STACK_SIZE <= 0
                         ? (void *)(DTCM_ARENA_START - SYSTEM_STACK_SIZE)
                         : (void *)((DTCM_SYSTEM_STACK - IRQ_STACK_SIZE) -
                                    SYSTEM_STACK_SIZE);

    data_0217002c.stackBottom = DTCM_SYSTEM_STACK - IRQ_STACK_SIZE;
    data_0217002c.stackTop = (u32)stackLow;
    data_0217002c.stackWarningOffset = 0;

    *(u32 *)(data_0217002c.stackBottom - sizeof(u32)) = 0xfddb597d;
    *(u32 *)data_0217002c.stackTop = 0x7bf9dd5b;

    Os_InitializeThreadQueue(&data_0217002c.joinQueue);

    data_0216ff5c.needsRescheduling = 0;
    data_0216ff5c.irqDepth = 0;

    *(OsThreadInfo *volatile *)0x027fffa0 = &data_0216ff5c;

    (void)Os_SetThreadSwitchCallback(0);

    Os_Thread_Create(&data_0216ff6c, Os_IdleThreadMain, 0,
                     &data_021701b4, 200, 0x1f);

    data_0216ff6c.priority = 0x20;
    data_0216ff6c.state = 1;
}
