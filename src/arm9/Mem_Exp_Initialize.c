typedef unsigned short u16;

typedef struct Mem_MemoryRegion {
    void *start;
    void *end;
} Mem_MemoryRegion;

typedef struct Mem_ExpHeapMemoryBlockList {
    void *head;
    void *tail;
} Mem_ExpHeapMemoryBlockList;

typedef struct Mem_ExpHeapHead {
    Mem_ExpHeapMemoryBlockList free_list;
    Mem_ExpHeapMemoryBlockList used_list;
    u16 group_id;
    u16 feature;
} Mem_ExpHeapHead;

typedef union Mem_CommonHeapHead {
    Mem_ExpHeapHead exp_heap_head;
    unsigned char data[0x14];
} Mem_CommonHeapHead;

typedef struct Mem_HeapHead {
    unsigned int magic;
    struct Mem_HeapHead *some_head;
    void *some_tail;
    unsigned char child_heap_head_list[0x0c];
    Mem_MemoryRegion heap_region;
    unsigned int option;
    Mem_CommonHeapHead common;
} Mem_HeapHead;

extern void Mem_InitializeHeapHead(Mem_HeapHead *heap_head, int magic,
                                   void *start, void *end, int option);
extern void *Mem_Exp_InitializeMemoryBlock(Mem_MemoryRegion *region,
                                           int magic);

// PURPOSE: Initializes an expandable heap over the supplied memory range.
Mem_HeapHead *Mem_Exp_Initialize(Mem_HeapHead *heap_head, void *end, int option)
{
    Mem_ExpHeapHead *exp_heap_head = &heap_head->common.exp_heap_head;
    Mem_MemoryRegion region;
    void *block;

    Mem_InitializeHeapHead(heap_head, 0x45585048, exp_heap_head + 1, end, option);
    exp_heap_head->group_id = 0;
    exp_heap_head->feature = 0;
    exp_heap_head->feature &= ~1;
    region.start = heap_head->heap_region.start;
    region.end = heap_head->heap_region.end;
    block = Mem_Exp_InitializeMemoryBlock(&region, 0x4652);
    exp_heap_head->free_list.head = block;
    exp_heap_head->free_list.tail = block;
    exp_heap_head->used_list.head = 0;
    exp_heap_head->used_list.tail = 0;
    return heap_head;
}
