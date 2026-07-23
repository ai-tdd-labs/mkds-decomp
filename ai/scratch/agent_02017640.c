/* PURPOSE: Finds the deepest heap that contains an address.
 * heapList is the list to search, and address is the byte address to locate.
 * Each matching heap's child list is searched before that heap is returned.
 * Returns null when no heap in the list contains the address.
 */

typedef struct HeapHead {
    unsigned char unknown00[0x0c];
    unsigned char childHeaps[0x0c];
    unsigned char *startAddress;
    unsigned char *endAddress;
} HeapHead;

extern HeapHead *IntrusiveListWrapper_NextItem(void *list, void *item);

HeapHead *Mem_FindTopParentHeapHead(void *heapList, unsigned char *address)
{
    HeapHead *heap = IntrusiveListWrapper_NextItem(heapList, 0);

    while (heap != 0) {
        if (heap->startAddress <= address && address < heap->endAddress) {
            HeapHead *child = Mem_FindTopParentHeapHead(heap->childHeaps, address);

            return child != 0 ? child : heap;
        }

        heap = IntrusiveListWrapper_NextItem(heapList, heap);
    }

    return 0;
}
