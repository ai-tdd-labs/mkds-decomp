typedef void (*sig_func)(int sig);
extern sig_func signal_funcs[7];

typedef struct OSMutex {
    unsigned char pad[0x18];
} OSMutex;

typedef struct OSThread {
    unsigned char pad[0x6c];
    unsigned int id;
} OSThread;

typedef struct OSThreadInfo {
    unsigned char pad[8];
    OSThread *current;
} OSThreadInfo;

extern OSThreadInfo ThreadInfo;
extern OSMutex __cs[9];
extern int __cs_id[9];
extern int __cs_ref[9];

extern int Os_Mutex_TryLock(OSMutex *mutex);
extern void Os_Mutex_Lock(OSMutex *mutex);
extern void Os_Mutex_Unlock(OSMutex *mutex);
extern void CheckZetaInvokeBeta(int code);

static inline void __begin_critical_region(int region) {
    OSThread *currentThread;

    if (Os_Mutex_TryLock(&__cs[region]) == 0) {
        currentThread = ThreadInfo.current;
        __cs_id[region] = currentThread->id;
        __cs_ref[region] = 1;
    } else {
        currentThread = ThreadInfo.current;
        if (currentThread->id == __cs_id[region]) {
            __cs_ref[region]++;
        } else {
            Os_Mutex_Lock(&__cs[region]);
            currentThread = ThreadInfo.current;
            __cs_id[region] = currentThread->id;
            __cs_ref[region] = 1;
        }
    }
}

static inline void __end_critical_region(int region) {
    if (--__cs_ref[region] == 0) {
        Os_Mutex_Unlock(&__cs[region]);
    }
}

int func_02139e20(int sig) {
    sig_func temp_r31;

    if (sig < 1 || sig > 7) {
        return -1;
    }

    __begin_critical_region(7);

    temp_r31 = signal_funcs[sig - 1];

    if ((unsigned int) temp_r31 != 1) {
        signal_funcs[sig - 1] = 0;
    }

    __end_critical_region(7);

    if ((unsigned int) temp_r31 == 1 || ((int) temp_r31 == 0 && sig == 1)) {
        return 0;
    }

    if ((unsigned int) temp_r31 == 0) {
        CheckZetaInvokeBeta(0);
    }

    temp_r31(sig);
    return 0;
}
