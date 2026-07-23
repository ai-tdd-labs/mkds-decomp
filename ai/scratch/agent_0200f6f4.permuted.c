// PURPOSE: Initializes the system tick timer once.

typedef unsigned short u16;
typedef unsigned int u32;

typedef struct TickQueue {
    u32 head;
    u32 tail;
} TickQueue;

extern u16 data_0217024c;
extern u32 data_02170250;
extern volatile TickQueue data_02170254;

extern u32 Os_ReserveTimer(u32 timer);
extern void Os_CountTicks(void);
extern void Os_SetIrqHandler(u32 mask, void (*handler)(void));
extern u32 Os_EnableIrqHandler(u32 mask);

void Os_InitializeTick(void)
{
    u16 one = 1;
    u16 *flag = &data_0217024c;

    if (*flag != 0) {
        return;
    }

    *flag = one;
    Os_ReserveTimer(0);
    data_02170254.head = 0;
    data_02170254.tail = 0;
    *(volatile u16 *)0x04000102 = 0;
    *(volatile u16 *)0x04000100 = 0;
    *(volatile u16 *)0x04000102 = 0xc1;
    Os_SetIrqHandler(8, Os_CountTicks);
    Os_EnableIrqHandler(8);
    data_02170250 = 0;
}
