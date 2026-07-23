/* PURPOSE: Starts the global AN worker thread.
 * The first argument is probably a work allocation containing the thread state.
 * The second argument is its total size; the remaining aligned space becomes
 * the worker stack. Later calls leave the original global worker unchanged. */

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct GlobalANWork {
    u8 thread[0xc0];
    u32 state;
    u8 controller[0x20];
    u8 stack[];
} GlobalANWork;

extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 irqState);
extern void StructANN_Create_from_thumb(void *controller);
extern void func_0200b08c(void *argument);
extern void Os_Thread_Create(void *thread, void (*entry)(void *), void *argument,
                            void *stackTop, u32 stackSize, u32 priority);
extern void Os_Thread_WakeUpDirect(void *thread);
extern GlobalANWork *data_0216fde0;

void InitializeSetGlobalAN_from_thumb(GlobalANWork *work, u32 totalSize)
{
    u32 irqState = Os_DisableIrq();

    if (data_0216fde0 == 0) {
        u32 stackSize;

        data_0216fde0 = work;
        StructANN_Create_from_thumb(work->controller);
        work->state = 0;

        /* Keep the stack top word-aligned within the supplied allocation. */
        stackSize = (totalSize - sizeof(GlobalANWork)) & ~3;
        Os_Thread_Create(work->thread, func_0200b08c, work,
                         work->stack + stackSize, stackSize, 0);
        Os_Thread_WakeUpDirect(work->thread);
    }

    Os_RestoreIrq(irqState);
}
