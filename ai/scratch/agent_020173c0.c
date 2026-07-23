// PURPOSE: Inserts an item before another item in an intrusive list.
// A null position appends the item, while the first position prepends it.
// Otherwise, the item is linked between the position and its predecessor.

typedef unsigned short u16;

typedef struct IntrusiveListLinks {
    void *previous;
    void *next;
} IntrusiveListLinks;

typedef struct IntrusiveListWrapper {
    void *first;
    void *last;
    u16 count;
    u16 linkOffset;
} IntrusiveListWrapper;

#define ITEM_LINKS(list, item) \
    ((IntrusiveListLinks *)((void *)(item) + (list)->linkOffset))

extern void IntrusiveListWrapper_InsertLast(IntrusiveListWrapper *list,
                                            void *item);
extern void IntrusiveListWrapper_InsertFirst(IntrusiveListWrapper *list,
                                             void *item);

void IntrusiveListWrapper_SomeFn_0(IntrusiveListWrapper *list, void *position,
                                   void *item)
{
    if (position == 0) {
        IntrusiveListWrapper_InsertLast(list, item);
    } else if (position == list->first) {
        IntrusiveListWrapper_InsertFirst(list, item);
    } else {
        IntrusiveListLinks *itemLinks = ITEM_LINKS(list, item);
        void *previous = ITEM_LINKS(list, position)->previous;
        IntrusiveListLinks *previousLinks = ITEM_LINKS(list, previous);

        itemLinks->previous = previous;
        itemLinks->next = position;
        previousLinks->next = item;
        ITEM_LINKS(list, position)->previous = item;
        list->count++;
    }
}
