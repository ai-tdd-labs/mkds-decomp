// PURPOSE: Moves a free award-track item into the active list.
// The supplied value is saved on the item, probably as its owner or target.
// If no free item is available, this returns null.

typedef unsigned short u16;

typedef struct IntrusiveListWrapper {
    void *first;
    void *last;
    u16 count;
    u16 linkOffset;
} IntrusiveListWrapper;

typedef struct AwardTrackItem {
    char pad_00[0x14];
    void *field_14;
    void *field_18;
    int field_1c;
} AwardTrackItem;

typedef struct AwardTrackManager {
    IntrusiveListWrapper activeItems;
    IntrusiveListWrapper groups;
    IntrusiveListWrapper freeItems;
} AwardTrackManager;

extern AwardTrackManager *data_0217b08c;

extern void *IntrusiveListWrapper_GetAtIndex(IntrusiveListWrapper *list,
                                             int index);
extern void IntrusiveListWrapper_RemoveItem(IntrusiveListWrapper *list,
                                            void *item);
extern void IntrusiveListWrapper_InsertLast(IntrusiveListWrapper *list,
                                            void *item);

void *func_0208ec64(void *arg0)
{
    AwardTrackItem *item;

    item = IntrusiveListWrapper_GetAtIndex(&data_0217b08c->freeItems, 0);
    if (item != 0) {
        item->field_14 = arg0;
        item->field_18 = 0;
        item->field_1c = 0x400;
        IntrusiveListWrapper_RemoveItem(&data_0217b08c->freeItems, item);
        IntrusiveListWrapper_InsertLast(&data_0217b08c->activeItems, item);
    }

    return item;
}
