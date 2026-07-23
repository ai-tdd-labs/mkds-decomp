// PURPOSE: Removes an object from the global object list.
// The argument is probably the object identifier stored by each list entry.
// The function disables interrupts while it searches and updates the list.
// It returns the removed entry, or zero if the object was not present.

typedef unsigned int u32;

typedef struct GlobalGO {
    void *object;
    char unknown_04[0x24];
    struct GlobalGO *next;
} GlobalGO;

extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 state);
extern void SetGlobalGO_from_thumb(GlobalGO *entry);
extern GlobalGO *GetGlobalGO_from_thumb(void);

GlobalGO *func_02006df8(void *object)
{
    u32 state;
    GlobalGO *previous;
    GlobalGO *entry;

    state = Os_DisableIrq();
    previous = GetGlobalGO_from_thumb();
    if (previous == 0) {
        Os_RestoreIrq(state);
        return 0;
    }

    if (previous->object == object) {
        SetGlobalGO_from_thumb(previous->next);
        Os_RestoreIrq(state);
        return previous;
    }

    entry = previous->next;
    while (entry != 0) {
        if (entry->object == object) {
            previous->next = entry->next;
            Os_RestoreIrq(state);
            return entry;
        }
        previous = entry;
        entry = entry->next;
    }

    Os_RestoreIrq(state);
    return 0;
}
