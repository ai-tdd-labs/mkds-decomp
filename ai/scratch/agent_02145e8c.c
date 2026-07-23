// PURPOSE: Queues a backup-card stream command and optionally runs it immediately.
// The arguments provide the transfer addresses, length, completion callback, and request settings.
// Access to the shared card state is serialized while interrupts are disabled.

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct CardCommand {
    u32 result;
} CardCommand;

typedef struct CardContext CardContext;
typedef void (*CardCallback)(void *argument);

struct CardContext {
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
    u32 requestMode;
    CardCallback callback;
    void *callbackArgument;
    void (*task)(CardContext *context);
    u8 thread[0xc0];
    void *currentThread;
    u32 threadPriority;
    u8 busyQueue[8];
    volatile u32 status;
    u8 reserved[8];
    u8 backupCache[0x100];
};

typedef struct OsThreadContext {
    u32 reserved;
    void *currentThread;
} OsThreadContext;

#define data_02000b70 ((char *)0x02000b70)
extern OsThreadContext data_0216ff5c;
extern CardContext data_0217fa40;

extern void Os_ReferSymbol(void *symbol);
extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 state);
extern void Os_Thread_Sleep(void *queue);
extern void Card_SetTask(void (*task)(CardContext *context));
extern void Card_BackupCommandTask(CardContext *context);

int Card_RequestStreamCommand(u32 source, u32 destination, u32 length,
                              CardCallback callback, void *callbackArgument,
                              int isAsync, int requestType, int retryCount,
                              int requestMode)
{
    CardContext *const state = &data_0217fa40;
    u32 irqState;

    Os_ReferSymbol(data_02000b70);

    irqState = Os_DisableIrq();
    while ((state->status & 4) != 0) {
        Os_Thread_Sleep(state->busyQueue);
    }
    state->status |= 4;
    state->callback = callback;
    state->callbackArgument = callbackArgument;
    Os_RestoreIrq(irqState);

    state->source = source;
    state->destination = destination;
    state->remainingLength = length;
    state->requestType = requestType;
    state->requestRetryCount = retryCount;
    state->requestMode = requestMode;

    if (isAsync) {
        Card_SetTask(Card_BackupCommandTask);
        return 1;
    } else {
        data_0217fa40.currentThread = data_0216ff5c.currentThread;
        Card_BackupCommandTask(state);
        return state->command->result == 0;
    }
}
