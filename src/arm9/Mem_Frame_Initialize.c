// PURPOSE: Initializes a frame heap over the supplied memory range.

typedef struct Mem_MemoryRegion {
    void *start;
    void *end;
} Mem_MemoryRegion;

typedef struct Mem_FrameHeapHead {
    Mem_MemoryRegion cur_heap_region;
    void *cur_state;
} Mem_FrameHeapHead;

typedef union Mem_CommonHeapHead {
    unsigned char exp_heap_head[0x14];
    Mem_FrameHeapHead frm_heap_head;
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

extern void Mem_InitializeHeapHead(Mem_HeapHead *out_head, int magic,
                                   void *start, void *end,
                                   int option);

Mem_HeapHead *Mem_Frame_Initialize(Mem_HeapHead *heap_head, void *end,
                                   int option)
{
    Mem_CommonHeapHead *common = &heap_head->common;

    Mem_InitializeHeapHead(heap_head, 0x46524D48,
                           &common->frm_heap_head + 1,
                           end, option);
    heap_head->common.frm_heap_head.cur_heap_region.start =
        heap_head->heap_region.start;
    common->frm_heap_head.cur_heap_region.end =
        heap_head->heap_region.end;
    common->frm_heap_head.cur_state = 0;
    return heap_head;
}
