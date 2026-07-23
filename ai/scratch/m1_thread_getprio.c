typedef struct OSThread { char pad[0x70]; int priority; } OSThread;
int Os_Thread_GetPriority(OSThread *thread) { return thread->priority; }
