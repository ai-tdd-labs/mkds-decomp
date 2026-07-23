// PURPOSE: Sets up a heap header and adds it to the heap list.
/*
 * The header receives its magic value, memory bounds, and a one-byte option.
 * Its child-list wrapper is initialized before the header is linked to its parent.
 * The global root list is probably initialized only once.
 */

typedef struct IntrusiveListWrapper {
    unsigned char data[0x0c];
} IntrusiveListWrapper;

typedef struct Mem_HeapHead {
    int magic;
    unsigned char unk_04[0x08];
    IntrusiveListWrapper child_heap_head_list;
    void *start;
    void *end;
    unsigned int option;
} Mem_HeapHead;

extern int data_02173264;
extern unsigned char data_02173268[];

extern void IntrusiveListWrapper_InitializeEmpty(IntrusiveListWrapper *list,
                                                 int item_size);
extern void IntrusiveListWrapper_InsertLast(IntrusiveListWrapper *list,
                                            void *item);
extern IntrusiveListWrapper *Mem_FindTopParentHeapHeadList(unsigned char *address);

void Mem_InitializeHeapHead(Mem_HeapHead *heap_head, int magic, void *start,
                            void *end, unsigned short option)
{
    heap_head->magic = magic;
    heap_head->start = start;
    heap_head->end = end;
    heap_head->option = 0;
    heap_head->option &= ~0xff;
    heap_head->option |= option & 0xff;
    IntrusiveListWrapper_InitializeEmpty(&heap_head->child_heap_head_list, 4);

    if (data_02173264 == 0) {
        IntrusiveListWrapper_InitializeEmpty(
            (IntrusiveListWrapper *)data_02173268, 4);
        data_02173264 = 1;
    }

    IntrusiveListWrapper_InsertLast(
        Mem_FindTopParentHeapHeadList((unsigned char *)heap_head), heap_head);
}
