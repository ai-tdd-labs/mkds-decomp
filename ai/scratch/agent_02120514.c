// PURPOSE: Releases the global state handler and resets its control flags.
// This function takes no arguments.
// It probably finalizes an optional expandable heap, frees its backing block,
// then clears the handler's state pointer and restores two halfword flags.

typedef unsigned short u16;

typedef struct HandlerFlags {
    unsigned char pad_00[0x10];
    u16 flag_10;
    u16 flag_12;
} HandlerFlags;

typedef struct GlobalStateHandler {
    void *expHeap;
    void *block;
    unsigned char pad_08[0x1f30 - 8];
    void *state;
} GlobalStateHandler;

extern GlobalStateHandler *data_0217d384;

extern void Mem_Exp_Finalize(void *heap);
extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void Mem_FreeHeap(void *heap, void *block);

void func_02120514(void)
{
    HandlerFlags *flags;

    if (data_0217d384->expHeap != 0) {
        Mem_Exp_Finalize(data_0217d384->expHeap);
        Mem_FreeHeap(ExecutionContext_GetHeapHandle(GetActiveExecutionContext()),
                     data_0217d384->block);
    }

    data_0217d384->state = 0;
    flags = (HandlerFlags *)((int)data_0217d384 + 8);
    flags->flag_10 = 0;
    flags->flag_12 = 1;
}
