/* PURPOSE: Initializes the vertical-alarm system once.
 * Takes no arguments and returns nothing.
 * Marks the system initialized, empties its alarm queue, disables the
 * associated IRQ handler, and clears the probably frame-related counters.
 */

typedef unsigned short u16;
typedef unsigned int u32;

typedef struct VAlarmQueue {
    void *head;
    void *tail;
} VAlarmQueue;

extern u16 data_02170268;
extern u32 data_0217026c;
extern u32 data_02170270;
extern VAlarmQueue data_02170274;

extern u32 Os_DisableIrqHandler(u32 mask);

void Os_InitializeVAlarm(void)
{
    if (data_02170268 != 0) {
        return;
    }

    data_02170268 = 1;
    data_02170274.head = 0;
    data_02170274.tail = 0;
    Os_DisableIrqHandler(4);
    data_02170270 = 0;
    data_0217026c = 0;
}
