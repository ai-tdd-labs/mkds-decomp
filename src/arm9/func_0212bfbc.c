// PURPOSE: Moves a loaded sound item into the current sound context.
// The first argument selects a probably per-context state slot, and the second
// is the context that receives the selected item. The item is removed from its
// old list before its loaded data is disposed, probably to reset its resources.

typedef unsigned char u8;

extern u8 data_0217d89c[];
extern void *IntrusiveListWrapper_NextItem(void *list, void *item);
extern void IntrusiveListWrapper_RemoveItem(void *list, void *item);
extern void Sound_Context_DisposeLoadedStuff(void *loadedStuff);

void *func_0212bfbc(int stateIndex, void *context)
{
    void *item;
    u8 *state;

    state = data_0217d89c + stateIndex * 0x24;
    item = IntrusiveListWrapper_NextItem(state + 0xc, 0);
    if (item == 0) {
        return 0;
    }

    IntrusiveListWrapper_RemoveItem(state + 0xc, item);
    *(void **)((u8 *)item + 0xc) = context;
    *(void **)((u8 *)context + 8) = item;
    Sound_Context_DisposeLoadedStuff(*(void **)((u8 *)item + 8));
    return *(void **)((u8 *)item + 8);
}
