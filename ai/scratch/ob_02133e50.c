typedef unsigned int u32;
typedef int s32;

typedef struct OSThread {
    unsigned char pad[0x6c];
    u32 id;
} OSThread;

typedef struct OSThreadInfo {
    unsigned char pad[8];
    OSThread *current;
} OSThreadInfo;

typedef struct OSMutex {
    unsigned char pad[0x18];
} OSMutex;

enum { atexit_funcs_access = 0 };

extern OSThreadInfo data_0216ff5c;
extern OSMutex data_0217eadc[9];
extern s32 data_0217ea94[9];
extern s32 data_0217eab8[9];

extern int Os_Mutex_TryLock(OSMutex *mutex);
extern void Os_Mutex_Lock(OSMutex *mutex);
extern void Os_Mutex_Unlock(OSMutex *mutex);

static inline OSThread *OS_GetCurrentThread(void) {
    return data_0216ff5c.current;
}

static inline u32 OS_GetThreadId(OSThread *thread) {
    return thread->id;
}

static inline void __begin_critical_region(int region) {
    OSThread *currentThread;

    if (Os_Mutex_TryLock(&data_0217eadc[region]) == 0) {
        currentThread = OS_GetCurrentThread();
        data_0217ea94[region] = OS_GetThreadId(currentThread);
        data_0217eab8[region] = 1;
    } else {
        currentThread = OS_GetCurrentThread();
        if (OS_GetThreadId(currentThread) == data_0217ea94[region]) {
            data_0217eab8[region]++;
        } else {
            Os_Mutex_Lock(&data_0217eadc[region]);
            currentThread = OS_GetCurrentThread();
            data_0217ea94[region] = OS_GetThreadId(currentThread);
            data_0217eab8[region] = 1;
        }
    }
}

static inline void __end_critical_region(int region) {
    if (--data_0217eab8[region] == 0) {
        Os_Mutex_Unlock(&data_0217eadc[region]);
    }
}

extern void (*data_0217e994[64])(void);
extern int data_0217e98c;
extern void (*data_0217e984)(void);

extern void func_021349c4(void *stream);
extern void func_02142590(void);

void func_02133e50(int status) {
    __begin_critical_region(atexit_funcs_access);

    while (data_0217e98c > 0) {
        data_0217e994[--data_0217e98c]();
    }

    __end_critical_region(atexit_funcs_access);

    if (data_0217e984 != 0) {
        data_0217e984();
        data_0217e984 = 0;
    }

    func_021349c4(0);
    func_02142590();
}
