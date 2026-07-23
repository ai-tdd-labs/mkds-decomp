// PURPOSE: Initializes the shared card subsystem context.
// This prepares the command buffer, lock queues, and worker thread.
// It also copies the ROM header when this console is not a multiboot child.
// The function takes no arguments and installs the card FIFO handler.

typedef unsigned int u32;
typedef unsigned short u16;

typedef struct ThreadQueue {
    void *head;
    void *tail;
} ThreadQueue;

typedef struct CardContext {
    void *command_buffer;
    int command;
    volatile int lock_owner;
    volatile int lock_ref;
    ThreadQueue lock_queue;
    int lock_target;
    u32 src;
    u32 dst;
    u32 len;
    u32 dma;
    int request_type;
    int request_retry;
    int request_mode;
    void *callback;
    void *callback_arg;
    void *task_func;
    unsigned char thread[0xc0];
    void *current_thread;
    u32 priority;
    ThreadQueue busy_queue;
    volatile u32 flags;
} CardContext;

extern CardContext data_0217fa40;
extern unsigned char data_0217fa00[];
extern unsigned char data_02180060[];

extern void Mem_CpuFastMemorySet(u32 value, void *destination, u32 size);
extern void Arm_FlushRange(void *address, u32 size);
extern void Mem_CpuCopy8(const volatile void *source, volatile void *destination,
                         u32 size);
extern void Os_Thread_Create(void *thread, void (*entry)(void *), void *argument,
                             void *stack, u32 stack_size, u32 priority);
extern void Os_Thread_WakeUpDirect(void *thread);
extern void Fifo_RegisterHandler(int tag, void (*handler)(int, int, int));
extern void Card_SetEnabled(int enabled);
extern void Card_ContextThreadMain(void *argument);
extern void Card_FifoHandler(int tag, int data, int error);

void Card_InitializeContext(void)
{
    CardContext *context = &data_0217fa40;
    volatile u32 clear_value;

    context->lock_owner = -3;
    context->lock_ref = 0;
    clear_value = 0;
    context->lock_target = 0;

    context->command_buffer = data_0217fa00;
    Mem_CpuFastMemorySet(clear_value, data_0217fa00, 0x40);
    Arm_FlushRange(data_0217fa00, 0x40);

    if (*(volatile u16 *)0x027ffc40 != 2) {
        Mem_CpuCopy8((const volatile void *)0x027ffe00,
                     (volatile void *)0x027ffa80, 0x160);
    }

    context->lock_queue.head = context->lock_queue.tail = 0;
    context->busy_queue.head = context->busy_queue.tail = 0;
    context->priority = 4;

    Os_Thread_Create(context->thread, Card_ContextThreadMain, 0,
                     data_02180060, 0x400, context->priority);
    Os_Thread_WakeUpDirect(context->thread);

    Fifo_RegisterHandler(0xb, Card_FifoHandler);

    if (*(volatile u16 *)0x027ffc40 != 2) {
        Card_SetEnabled(1);
    }
}
