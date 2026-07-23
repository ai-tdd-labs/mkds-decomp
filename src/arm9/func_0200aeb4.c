// PURPOSE: Sends a command to the global AN worker safely.
// The argument is probably the command payload forwarded to the worker.
// It only sends the command when the global AN worker is ready.

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct GlobalANWork {
    u8 thread[0xc4];
} GlobalANWork;

extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 irqState);
extern int IsGlobalANSet_from_thumb(void);
extern void StructANN_SomeFn_from_thumb(void *controller, int commandType,
                                        void *payload, int value);
extern GlobalANWork *data_0216fde0;

void func_0200aeb4(void *payload)
{
    u32 irqState = Os_DisableIrq();

    if (IsGlobalANSet_from_thumb() != 0) {
        /* The controller starts immediately after the thread storage. */
        StructANN_SomeFn_from_thumb(data_0216fde0->thread + 0xc4, 0, payload, 0);
    }

    Os_RestoreIrq(irqState);
}
