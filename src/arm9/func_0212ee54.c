// PURPOSE: Adds an item to the shared interrupt-safe list.
// The item is appended while interrupts are disabled.
// The saved interrupt state is restored before returning.

typedef unsigned int u32;

typedef struct IntrusiveListWrapper IntrusiveListWrapper;

extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 state);
extern void IntrusiveListWrapper_InsertLast(IntrusiveListWrapper *list, void *item);
extern IntrusiveListWrapper data_0217df08;

void func_0212ee54(void *item)
{
    u32 state;

    state = Os_DisableIrq();
    IntrusiveListWrapper_InsertLast(&data_0217df08, item);
    Os_RestoreIrq(state);
}
