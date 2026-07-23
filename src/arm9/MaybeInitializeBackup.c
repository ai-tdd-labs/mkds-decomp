// PURPOSE: Starts the backup card operation and reports whether it succeeded.
// The argument probably identifies the backup command prepared by the card system.
// It locks shared card state, performs two requests, and then wakes waiting threads.
// A registered completion callback receives its saved argument after the operation.

typedef unsigned int u32;
typedef unsigned char u8;

typedef struct CardCommand {
    u32 result;
    u32 type;
    u32 id;
    u32 source;
    u32 destination;
    u32 length;
} CardCommand;

typedef void (*CardCallback)(void *argument);

typedef struct CardContext {
    CardCommand *command;
    u8 pad_004[0x34];
    CardCallback callback;
    void *callbackArgument;
    void (*task)(struct CardContext *context);
    u8 thread[0xc0];
    void *currentThread;
    u32 threadPriority;
    u8 sleepQueue[8];
    volatile u32 status;
    u8 pad_118[8];
    u8 backupCache[0x100];
} CardContext;

typedef struct OsThreadContext {
    u32 pad_000;
    void *currentThread;
} OsThreadContext;

#define data_02000b70 ((char *)0x02000b70)
extern OsThreadContext data_0216ff5c;
extern CardContext data_0217fa40;

extern void Os_ReferSymbol(const char *symbol);
extern void Os_Terminate(void);
extern void EnsureCardEnabled(void);
extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 state);
extern void Os_Thread_Sleep(void *queue);
extern void func_02145b54(void *argument);
extern int Card_Request(CardContext *context, int requestType, int retryCount);
extern void Os_Thread_WakeUp(void *queue);
extern void Os_Thread_WakeUpDirect(void *thread);

int MaybeInitializeBackup(void *argument)
{
    CardContext *state = &data_0217fa40;
    CardCallback callback;
    void *callbackArgument;
    u32 irqState;

    Os_ReferSymbol(data_02000b70);
    if (argument == 0) {
        Os_Terminate();
    }

    EnsureCardEnabled();
    irqState = Os_DisableIrq();
    while ((state->status & 4) != 0) {
        Os_Thread_Sleep(state->sleepQueue);
    }
    state->status |= 4;
    state->callback = 0;
    state->callbackArgument = 0;
    Os_RestoreIrq(irqState);

    func_02145b54(argument);
    data_0217fa40.currentThread = data_0216ff5c.currentThread;
    Card_Request(state, 2, 1);
    state->command->source = 0;
    state->command->destination = (u32)state->backupCache;
    state->command->length = 1;
    Card_Request(state, 6, 1);

    callback = state->callback;
    callbackArgument = state->callbackArgument;
    irqState = Os_DisableIrq();
    state->status &= ~0x4c;
    Os_Thread_WakeUp(state->sleepQueue);
    if ((state->status & 0x10) != 0) {
        Os_Thread_WakeUpDirect(state->thread);
    }
    Os_RestoreIrq(irqState);

    if (callback != 0) {
        callback(callbackArgument);
    }
    return state->command->result == 0;
}
