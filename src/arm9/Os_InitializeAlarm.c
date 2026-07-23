// PURPOSE: Initializes the alarm system once.
// This function takes no arguments and returns nothing.
// It reserves a timer, clears the probably alarm queue, and disables its IRQ.

typedef unsigned short u16;
typedef unsigned int u32;

typedef struct AlarmQueue {
    u32 head;
    u32 tail;
} AlarmQueue;
extern AlarmQueue data_02170260;
extern volatile u16 data_0217025c[];

extern u32 Os_ReserveTimer(void);
extern u32 Os_DisableIrqHandler(u32 mask);

void Os_InitializeAlarm(void)
{
    u16 *flag = (u16 *)data_0217025c;

    if (*flag != 0) {
        return;
    }

    *flag = 1;
    Os_ReserveTimer();

    /* Clear the two queue links before disabling the alarm IRQ. */
    data_02170260.head = 0;
    data_02170260.tail = 0;
    Os_DisableIrqHandler(16);
}
