// PURPOSE: Removes an item and clears its associated pointer.
// The first argument is probably a list wrapper containing a byte offset.
// The second argument is the base for the referenced record.
// If that record still has a pointer at offset eight, it is cleared.

typedef unsigned short u16;

typedef struct ListWrapper {
    char pad[0x0a];
    u16 itemOffset;
} ListWrapper;

typedef struct ItemRecord {
    char pad[8];
    void *item;
} ItemRecord;

extern void IntrusiveListWrapper_RemoveItem(void *wrap);

void func_0210bc54(ListWrapper *wrap, char *base)
{
    ItemRecord *record;

    IntrusiveListWrapper_RemoveItem(wrap);
    record = (ItemRecord *)(base + wrap->itemOffset);
    if (record->item != 0)
        record->item = 0;
}
