// PURPOSE: Waits until a lock attempt can be handled.
// The four arguments describe the lock operation passed to the handler.
// It probably waits for another thread when the handler reports contention.

extern int Os_Lock_HandleTryLock(void *arg0, void *arg1, void *arg2, void *arg3);
extern void Os_Lock_Wait(void);

void Os_Lock_TryLockImpl(void *arg0, void *arg1, void *arg2, void *arg3)
{
    while (Os_Lock_HandleTryLock(arg0, arg1, arg2, arg3) > 0) {
        Os_Lock_Wait();
    }
}
