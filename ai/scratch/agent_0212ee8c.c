// PURPOSE: Moves every matching item out of a list while interrupts are disabled.
// The list and the value to match are supplied by the caller.
// Matching entries are removed and probably returned to the shared list.

typedef unsigned int u32;

typedef struct IntrusiveListWrapper IntrusiveListWrapper;

typedef struct ListItem {
    void *previous;
    void *next;
    void *value;
} ListItem;

extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 state);
extern ListItem *IntrusiveListWrapper_NextItem(IntrusiveListWrapper *list, ListItem *item);
extern void IntrusiveListWrapper_RemoveItem(IntrusiveListWrapper *list, ListItem *item);
extern void func_0212ee54(void *item);

void func_0212ee8c(IntrusiveListWrapper *list, void *value)
{
    ListItem *next;
    ListItem *item;
    u32 state;

    state = Os_DisableIrq();
    item = IntrusiveListWrapper_NextItem(list, 0);
    while (item != 0) {
        next = IntrusiveListWrapper_NextItem(list, item);
        if (item->value == value) {
            IntrusiveListWrapper_RemoveItem(list, item);
            func_0212ee54(item);
        }
        item = next;
    }
    Os_RestoreIrq(state);
}
