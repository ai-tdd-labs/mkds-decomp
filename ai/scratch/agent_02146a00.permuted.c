// PURPOSE: Clears the card completion flag and wakes the card worker.
typedef struct CardFifoWork {
    unsigned char pad_000[0x104];
    void *thread;
    unsigned char pad_108[0xc];
    volatile int flags;
} CardFifoWork;

extern CardFifoWork data_0217fa40;
extern void Os_Thread_WakeUpDirect(void *thread);

void Card_FifoHandler(int command, int unused, void *data)
{
    if (command != 11) {
        return;
    }

    if (data == 0) {
        return;
    }

    data_0217fa40.flags &= ~0x20;
    Os_Thread_WakeUpDirect(data_0217fa40.thread);
}
