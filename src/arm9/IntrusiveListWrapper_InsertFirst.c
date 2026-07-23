/* PURPOSE: Adds an item to the front of an intrusive list.
 * list holds the first item, item count, and the offset of each item's links.
 * item becomes the new first item; the helper handles an empty list.
 */

typedef unsigned short u16;

typedef struct IntrusiveListWrapper {
    void *first;
    void *last;
    u16 count;
    u16 linkOffset;
} IntrusiveListWrapper;

typedef struct IntrusiveListLinks {
    void *previous;
    void *next;
} IntrusiveListLinks;

extern void IntrusiveListWrapper_InsertFirstItem(IntrusiveListWrapper *list,
                                                 void *item);

void IntrusiveListWrapper_InsertFirst(IntrusiveListWrapper *list, void *item)
{
    IntrusiveListLinks *itemLinks;

    if (list->first == 0) {
        IntrusiveListWrapper_InsertFirstItem(list, item);
        return;
    }

    itemLinks = (IntrusiveListLinks *)((char *)item + list->linkOffset);
    itemLinks->previous = 0;
    itemLinks->next = list->first;

    /* Link the old first item back to its new predecessor. */
    ((IntrusiveListLinks *)((char *)list->first + list->linkOffset))->previous = item;
    list->first = item;
    list->count++;
}
