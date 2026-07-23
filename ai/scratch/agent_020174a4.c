/* PURPOSE: Adds an item to the end of an intrusive list.
 * list holds the first item, last item, item count, and link-field offset.
 * item becomes the new last item; the helper handles an empty list.
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

void IntrusiveListWrapper_InsertLast(IntrusiveListWrapper *list, void *item)
{
    IntrusiveListLinks *itemLinks;

    if (list->first == 0) {
        IntrusiveListWrapper_InsertFirstItem(list, item);
        return;
    }

    itemLinks = (IntrusiveListLinks *)((char *)item + list->linkOffset);
    itemLinks->previous = list->last;
    itemLinks->next = 0;

    /* Link the old last item forward to its new successor. */
    ((IntrusiveListLinks *)((char *)list->last + list->linkOffset))->next = item;
    list->last = item;
    list->count++;
}
