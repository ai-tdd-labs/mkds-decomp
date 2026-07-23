// PURPOSE: Sends a request to the game card processor and waits for completion.
// The context owns the shared command block and request status flags.
// The request type selects the operation, while retryCount limits timeout retries.

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct CardCommand {
    u32 result;
    u8 reserved[0x3c];
} CardCommand;

typedef struct CardContext {
    CardCommand *command;
    int currentCommand;
    u8 reserved[0x10c];
    volatile u32 status;
} CardContext;

extern int Fifo_IsHandlerReady(int tag, int processor);
extern void Os_SpinWait(u32 cycles);
extern void Arm_FlushRange(void *address, u32 size);
extern void Mem_DcDrainWriteBuffer(void);
extern int Fifo_SendWord(int tag, u32 data, int wait);
extern u32 Os_DisableIrq(void);
extern u32 Os_RestoreIrq(u32 state);
extern void Os_Thread_Sleep(void *queue);

static inline void Card_SendWord(u32 data)
{
    while (Fifo_SendWord(11, data, 1) < 0) {
    }
}

int Card_Request(CardContext *context, int requestType, int retryCount)
{
    if ((context->status & 2) == 0) {
        context->status |= 2;
        while (!Fifo_IsHandlerReady(11, 1)) {
            Os_SpinWait(100);
        }

        (void)Card_Request(context, 0, 1);
    }

    Arm_FlushRange(context->command, sizeof(*context->command));
    Mem_DcDrainWriteBuffer();

    do {
        context->currentCommand = requestType;
        context->status |= 0x20;
        Card_SendWord((u32)requestType);

        switch (requestType) {
        case 0:
            Card_SendWord((u32)context->command);
            break;
        }

        {
            u32 irqState = Os_DisableIrq();

            while ((context->status & 0x20) != 0) {
                Os_Thread_Sleep(0);
            }
            (void)Os_RestoreIrq(irqState);
        }
    } while ((context->command->result == 4) && (--retryCount > 0));

    return context->command->result == 0;
}
