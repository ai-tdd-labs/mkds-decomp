// PURPOSE: Stops the worker thread if it is still running.
// This function has no arguments and returns no value.
// It probably uses the thread object stored 0x400 bytes into data_021759d8.
// The thread is woken and joined repeatedly until it reports termination.

typedef struct OSThread OSThread;

extern void Os_Thread_WakeUpDirect(OSThread *thread);
extern void Os_Thread_Join(OSThread *thread);
extern int Os_Thread_IsTerminated(OSThread *thread);
extern unsigned char data_021759d8[];

void func_0204ba8c(void)
{
    if (Os_Thread_IsTerminated((OSThread *)((unsigned int)data_021759d8 + 0x400))) {
        return;
    }

    do {
        Os_Thread_WakeUpDirect((OSThread *)((unsigned int)data_021759d8 + 0x400));
        Os_Thread_Join((OSThread *)((unsigned int)data_021759d8 + 0x400));
    } while (!Os_Thread_IsTerminated((OSThread *)((unsigned int)data_021759d8 + 0x400)));
}
