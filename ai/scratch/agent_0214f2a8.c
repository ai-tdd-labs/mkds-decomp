// PURPOSE: Starts automatic microphone sampling with a validated configuration.
// The parameter block selects the format, buffer, interval, and loop behavior.
// The other arguments are saved as the completion callback and its user value.
// Interrupts protect the shared microphone operation while it is claimed.

typedef unsigned int u32;
typedef unsigned char u8;

typedef void (*MicCallback)(void *arg);

typedef struct MicAutoParam {
    int type;
    void *buffer;
    u32 size;
    u32 interval;
    int loopEnabled;
    MicCallback fullCallback;
    void *fullCallbackArg;
} MicAutoParam;

typedef struct MicOperation {
    int active;
    MicCallback callback;
    void *callbackArg;
    int result;
    MicCallback fullCallback;
    void *fullCallbackArg;
} MicOperation;

extern MicOperation data_02180414;
extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 irqState);
extern int func_0214ef34(u32 bufferAddress, u32 bufferSize, u32 interval,
                         u8 format);

int func_0214f2a8(const MicAutoParam *param, MicCallback callback,
                  void *callbackArg)
{
    int formatCode;
    u8 format;
    u32 irqState;

    if (((u32)param->buffer & 0x1f) != 0) {
        return 2;
    }
    if ((param->size & 0x1f) != 0) {
        return 2;
    }
    if (param->size == 0) {
        return 2;
    }
    if (param->interval < 0x400) {
        return 2;
    }

    switch (param->type) {
    case 0:
        formatCode = 0;
        break;
    case 1:
        formatCode = 1;
        break;
    case 2:
        formatCode = 2;
        break;
    case 3:
        formatCode = 3;
        break;
    case 4:
        formatCode = 5;
        break;
    case 5:
        formatCode = 7;
        break;
    default:
        return 2;
    }

    // Keep the narrowing in both arms before saving the final byte value.
    format = param->loopEnabled != 0
                 ? (u8)(formatCode | 0x10)
                 : (u8)formatCode;

    irqState = Os_DisableIrq();
    if (data_02180414.active != 0) {
        Os_RestoreIrq(irqState);
        return 1;
    }

    data_02180414.active = 1;
    Os_RestoreIrq(irqState);

    data_02180414.callback = callback;
    data_02180414.callbackArg = callbackArg;
    data_02180414.fullCallback = param->fullCallback;
    data_02180414.fullCallbackArg = param->fullCallbackArg;

    if (func_0214ef34((u32)param->buffer, param->size, param->interval,
                      format) != 0) {
        return 0;
    }
    return 3;
}
