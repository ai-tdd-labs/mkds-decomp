// PURPOSE: Allocates aligned memory from the shared race heap safely.
// The first argument is probably an unused allocator context.
// Allocation occurs with interrupts disabled and restores the prior state.

typedef unsigned int u32;

typedef struct RaceState {
    void *heap;
} RaceState;

extern RaceState *data_0217d384;

extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 state);
extern void *Mem_AllocateHeapAligned(void *heap, u32 size, u32 alignment);

void *func_0211fffc(void *unused, u32 size, u32 alignment)
{
    u32 irqState;
    void *memory;

    irqState = Os_DisableIrq();
    memory = Mem_AllocateHeapAligned(data_0217d384->heap, size, alignment);
    Os_RestoreIrq(irqState);
    return memory;
}
