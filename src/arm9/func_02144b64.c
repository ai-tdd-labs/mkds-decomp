// PURPOSE: Handles wireless data events for an active receive context.
// The argument identifies the callback slot, event type, and receive context.
// Valid data events append a halfword to a four-entry ring buffer.
// Other events update the context state and probably cancel a pending entry.

typedef unsigned char u8;
typedef unsigned short u16;

typedef void (*WmCallback)(void);

typedef struct {
    void *buffer1;
    void *buffer2;
    u8 pad_008[0xc4 - 0x008];
    WmCallback callbacks[16];
    void *callbackArgs[16];
} WmGlobal;

typedef struct {
    u8 pad_000[0x800];
    u16 values[4];
    u16 field_808;
    u16 cursor;
    u8 pad_80c[0x81c - 0x80c];
    u16 state;
} ReceiveContext;

typedef struct {
    u16 field_00;
    u16 eventType;
    u8 pad_04[0x0a - 0x04];
    u16 callbackSlot;
    u8 pad_0c[0x1a - 0x0c];
    u16 value;
    u8 pad_1c[0x20 - 0x1c];
    ReceiveContext *context;
} WmEvent;

extern WmGlobal *Wm_GetGlobal(void);
extern void DC_InvalidateRangeNoClean(void *start, unsigned int size);
extern void func_02144a50(void);
extern void func_02144920(void);

void func_02144b64(WmEvent *event)
{
    void *buffer;
    ReceiveContext *context;
    WmCallback callback;
    WmGlobal *global;
    u16 pending;

    global = Wm_GetGlobal();
    buffer = global->buffer2;
    callback = global->callbacks[event->callbackSlot];
    context = global->callbackArgs[event->callbackSlot];

    if (callback != func_02144a50 && callback != func_02144920)
        return;
    if (context == 0)
        return;
    if (context != event->context)
        return;

    DC_InvalidateRangeNoClean((u8 *)buffer + 0x184, 2);
    pending = *(u16 *)((u8 *)buffer + 0x184);

    if (event->eventType == 0) {
        if (pending != 0)
            return;

        context->values[context->cursor] = event->value >> 1;
        context->cursor = (context->cursor + 1) & 3;
        return;
    }

    if (event->eventType == 10) {
        if (pending != 0)
            context->cursor = (context->cursor + 3) & 3;
        context->state = 4;
        return;
    }

    context->state = 5;
}
