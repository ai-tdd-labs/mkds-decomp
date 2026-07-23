typedef struct OSThread { char pad[0x64]; int state; } OSThread;
int Os_Thread_IsTerminated(OSThread *thread) { return thread->state == 2; }
