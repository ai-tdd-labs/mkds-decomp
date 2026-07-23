typedef unsigned int u32;

typedef struct OSThread {
    unsigned char pad[0x68];
    struct OSThread *next;
} OSThread;

typedef struct OSThreadInfo {
    unsigned char pad[8];
    OSThread *list;
} OSThreadInfo;

extern OSThreadInfo data_0216ff5c;

void Os_PopThread(OSThread *thread) {
    OSThread *t = data_0216ff5c.list;
    OSThread *pre = 0;

    while (t && t != thread) {
        pre = t;
        t = t->next;
    }

    if (!pre) {
        data_0216ff5c.list = thread->next;
    } else {
        pre->next = thread->next;
    }
}
