// PURPOSE: Initializes the FIFO link used to communicate with the ARM7 processor.
// It clears the ARM9 callback state, installs the receive interrupt, and enables the FIFO.
// The final handshake waits for the other processor to acknowledge the interface.

typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;

typedef void (*FifoCallback)(s32 tag, u32 data, s32 error);

typedef struct SystemWork {
    unsigned char unknown_000[0x388];
    u32 pxiHandleCheckerArm9;
} SystemWork;

extern u16 data_02180328;
extern FifoCallback data_0218032c[32];

extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 state);
extern u32 SetIF(u32 mask);
extern void Os_SetIrqHandler(u32 mask, void (*handler)(void));
extern u32 Os_EnableIrqHandler(u32 mask);
extern void FIFONotEmptyIRQHandler(void);

void Fifo_Initialize(void)
{
    SystemWork *work = (SystemWork *)0x027ffc00;
    u32 irqState = Os_DisableIrq();
    s32 i;

    if (data_02180328 == 0) {
        data_02180328 = 1;
        work->pxiHandleCheckerArm9 = 0;

        for (i = 0; i < 32; i++) {
            data_0218032c[i] = 0;
        }

        *(volatile u16 *)0x04000184 = 0xc408;
        (void)SetIF(0x40000);
        Os_SetIrqHandler(0x40000, FIFONotEmptyIRQHandler);
        (void)Os_EnableIrqHandler(0x40000);

        {
            s32 timeout;
            s32 value;

            for (i = 0; ; i++) {
                value = *(volatile u16 *)0x04000180 & 15;
                *(volatile u16 *)0x04000180 = (u16)(value << 8);

                if (value == 0 && i > 4) {
                    break;
                }

                for (timeout = 1000;
                     (*(volatile u16 *)0x04000180 & 15) == value;
                     timeout--) {
                    if (timeout == 0) {
                        i = 0;
                        break;
                    }
                }
            }
        }
    }

    Os_RestoreIrq(irqState);
}
