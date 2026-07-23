// PURPOSE: Creates the global B state handler.
// The supplied heap provides storage for the handler state.
// It probably connects the state table and enables its initial two flags.

typedef unsigned short u16;

typedef struct GlobalBHandler {
    char _00[0x10];
    volatile u16 flag_18;
    volatile u16 flag_1a;
} GlobalBHandler;

typedef struct GlobalB {
    char _00[8];
    GlobalBHandler handler;
} GlobalB;

extern void *Mem_AllocateHeapAligned(void *heap, unsigned int size, unsigned int alignment);
extern void StateDualHandler_Create(void *handler, const void *stateTable,
                                    int stateCount, void *owner);
extern char data_0217d384[];
extern GlobalB *data_0216e21c;

void InitializeGlobalB_from_thumb(void *heap)
{
    GlobalBHandler *handler;

    data_0216e21c = Mem_AllocateHeapAligned(heap, 0x1f58, 0x20);
    StateDualHandler_Create((char *)data_0216e21c + 8, data_0217d384, 8, 0);
    handler = &data_0216e21c->handler;
    handler->flag_18 = 0;
    handler->flag_1a = 1;
}
