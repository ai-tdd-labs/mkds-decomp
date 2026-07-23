// PURPOSE: Detaches a sound entry and returns its pending object to its old list.

typedef unsigned char u8;

typedef struct IntrusiveListWrapper IntrusiveListWrapper;

typedef struct SoundListEntry {
    void *owner;
    IntrusiveListWrapper *list;
    void *pendingList;
    u8 unknown0c[0x20];
    u8 status;
} SoundListEntry;

extern void IntrusiveListWrapper_RemoveItem(void *list, void *item);
extern void IntrusiveListWrapper_InsertLast(IntrusiveListWrapper *list, void *item);
extern u8 data_0217d450[];
extern IntrusiveListWrapper data_0217d444;

void func_0212bd6c(SoundListEntry *entry)
{
    IntrusiveListWrapper *oldList;

    if (entry->owner != 0) {
        *(void **)entry->owner = 0;
        entry->owner = 0;
    }

    oldList = entry->list;
    IntrusiveListWrapper_RemoveItem(oldList, entry);
    entry->list = 0;

    if (entry->pendingList != 0) {
        IntrusiveListWrapper_InsertLast((IntrusiveListWrapper *)((u8 *)oldList + 0xc),
                                        entry->pendingList);
        *(void **)((u8 *)entry->pendingList + 0xc) = 0;
        entry->pendingList = 0;
    }

    IntrusiveListWrapper_RemoveItem(data_0217d450, entry);
    IntrusiveListWrapper_InsertLast(&data_0217d444, entry);
    entry->status = 0;
}
