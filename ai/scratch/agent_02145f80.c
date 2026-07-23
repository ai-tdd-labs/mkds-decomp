// PURPOSE: Transfers backup data between memory and the game card.
// The context supplies the source, destination, byte count, and request mode.
// Data moves through a 256-byte cache until the request finishes or fails.
// Waiting threads and an optional callback are notified when the task ends.

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct CardCommand {
    u32 result;
    u32 type;
    u32 id;
    u32 source;
    u32 destination;
    u32 length;
    u8 remaining[0x28];
} CardCommand;

typedef void (*CardCallback)(void *argument);

typedef struct CardContext {
    CardCommand *command;
    u32 currentCommand;
    u32 lockOwner;
    u32 lockCount;
    u8 lockQueue[8];
    u32 lockTarget;
    u32 source;
    u32 destination;
    u32 remainingLength;
    u32 dmaChannel;
    u32 requestType;
    u32 requestRetryCount;
    int requestMode;
    CardCallback callback;
    void *callbackArgument;
    void (*task)(struct CardContext *context);
    u8 thread[0xc0];
    void *currentThread;
    u32 threadPriority;
    u8 busyQueue[8];
    volatile u32 status;
    u8 reserved[8];
    u8 backupCache[0x100];
} CardContext;

extern void Os_ReferSymbol(const char *symbol);
extern char data_02000b70[];
extern void DC_InvalidateRangeNoClean(void *start, u32 length);
extern void Arm_FlushRange(void *start, u32 length);
extern void Mem_DcDrainWriteBuffer(void);
extern void Mem_CpuCopy8(const void *source, void *destination, u32 length);
extern int Card_Request(CardContext *context, int requestType, int retryCount);
extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 irqState);
extern void Os_Thread_WakeUp(void *queue);
extern void Os_Thread_WakeUpDirect(void *thread);

void Card_BackupCommandTask(CardContext *context)
{
    const int requestType = context->requestType;
    const int requestMode = context->requestMode;
    const int retryCount = context->requestRetryCount;
    u32 bufferSize;

    Os_ReferSymbol(data_02000b70);
    bufferSize = sizeof(context->backupCache);
    volatile int retryOne = 1;

    do {
        const u32 transferLength =
            (bufferSize < context->remainingLength) ? bufferSize : context->remainingLength;

        context->command->length = transferLength;

        if ((context->status & 0x40) != 0) {
            context->status &= ~0x40;
            context->command->result = 7;
            break;
        }

        if (requestMode == 0) {
            DC_InvalidateRangeNoClean(context->backupCache, transferLength);
            context->command->source = context->source;
            context->command->destination = (u32)context->backupCache;
        } else {
            Mem_CpuCopy8((const void *)context->source, context->backupCache, transferLength);
            Arm_FlushRange((u8 *)context + 0x120, transferLength);
            Mem_DcDrainWriteBuffer();
            context->command->source = (u32)context->backupCache;
            context->command->destination = context->destination;
        }

        if (!Card_Request(context, requestType, retryCount)) {
            break;
        }

        if (requestMode == 2) {
            if (!Card_Request(context, 9, retryOne)) {
                break;
            }
        } else if (requestMode == 0) {
            Mem_CpuCopy8(context->backupCache, (void *)context->destination, transferLength);
        }

        context->source += transferLength;
        context->destination += transferLength;
        context->remainingLength -= transferLength;
    } while (context->remainingLength > 0);

    {
        const CardCallback callback = context->callback;
        void *const callbackArgument = context->callbackArgument;
        u32 irqState = Os_DisableIrq();

        context->status &= ~0x4c;
        Os_Thread_WakeUp(context->busyQueue);
        if ((context->status & 0x10) != 0) {
            Os_Thread_WakeUpDirect(context->thread);
        }
        Os_RestoreIrq(irqState);

        if (callback != 0) {
            callback(callbackArgument);
        }
    }
}
