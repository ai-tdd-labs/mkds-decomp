// PURPOSE: Gets the item at a requested position in a list.
// list is the intrusive list wrapper to inspect and index is the zero-based position.
// It walks the list from its first item and returns null when the position is absent.
// The underlying item type is probably private to the list implementation.

extern void *IntrusiveListWrapper_NextItem(void *list, void *item);

void *IntrusiveListWrapper_GetAtIndex(void *list, int index)
{
    int currentIndex = 0;
    void *item = IntrusiveListWrapper_NextItem(list, 0);

    while (item != 0) {
        if (currentIndex == index)
            return item;

        currentIndex++;
        item = IntrusiveListWrapper_NextItem(list, item);
    }

    return 0;
}
