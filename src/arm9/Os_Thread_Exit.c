// PURPOSE: Ends the current operating-system thread.
// It disables interrupts before passing the active thread to the thread-exit handler.
// The handler receives no destructor argument.

typedef struct Os_Thread Os_Thread;

typedef struct OsThreadContext {
    int reserved;
    Os_Thread *currentThread;
} OsThreadContext;

extern OsThreadContext data_0216ff5c;
extern unsigned int Os_DisableIrq(void);
extern void Os_Thread_ExitImpl(Os_Thread *thread, void *destructorArgument);

void Os_Thread_Exit(void)
{
    Os_DisableIrq();
    Os_Thread_ExitImpl(data_0216ff5c.currentThread, 0);
}
