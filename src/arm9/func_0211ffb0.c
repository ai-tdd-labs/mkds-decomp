// PURPOSE: Frees a block from the shared heap when one is provided.
// The first argument is probably an unused heap context.
// A null block is ignored, and heap access is protected from interrupts.

typedef unsigned int u32;

extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 state);
extern void Mem_FreeHeap(void *heap, void *block);
extern void *data_0217d384;

void func_0211ffb0(void *unused, void *block)
{
    u32 state;

    if (block == 0) {
        return;
    }

    state = Os_DisableIrq();
    Mem_FreeHeap(*(void **)data_0217d384, block);
    Os_RestoreIrq(state);
}
