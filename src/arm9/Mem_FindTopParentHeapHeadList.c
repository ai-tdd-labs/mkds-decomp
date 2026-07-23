// PURPOSE: Finds the list after the deepest heap containing an address.
// The address is searched for in the main heap list.
// If no containing heap is found, this probably returns the list head itself.

typedef struct HeapHead HeapHead;

extern unsigned char data_02173268[];
extern HeapHead *Mem_FindTopParentHeapHead(void *heapList, unsigned char *address);

HeapHead *Mem_FindTopParentHeapHeadList(unsigned char *address) {
    HeapHead *list = (HeapHead *)data_02173268;
    HeapHead *found = Mem_FindTopParentHeapHead(list, address);

    if (found != 0) {
        list = (HeapHead *)((unsigned char *)found + 0xc);
    }
    return list;
}
