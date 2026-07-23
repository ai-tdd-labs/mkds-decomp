// PURPOSE: Resizes an allocated block in an expandable heap.
// The heap and block arguments identify the allocation to change.
// Growing consumes an adjacent free block; shrinking frees the unused tail.
// The return value is the resulting size, or zero when growth is impossible.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Mem_HeapHead {
    u8 padding_00[0x20];
    u32 option;
} Mem_HeapHead;

typedef struct Mem_ExpHeapMemoryBlock Mem_ExpHeapMemoryBlock;

struct Mem_ExpHeapMemoryBlock {
    u16 signature;
    u16 attribute;
    u32 block_size;
    Mem_ExpHeapMemoryBlock *previous;
    Mem_ExpHeapMemoryBlock *next;
};

typedef struct Mem_ExpHeapMemoryBlockList {
    Mem_ExpHeapMemoryBlock *head;
    Mem_ExpHeapMemoryBlock *tail;
} Mem_ExpHeapMemoryBlockList;

typedef struct Mem_ExpHeapHead {
    Mem_ExpHeapMemoryBlockList free_list;
    Mem_ExpHeapMemoryBlockList used_list;
    u16 group_id;
    u16 feature;
} Mem_ExpHeapHead;

typedef struct Mem_MemoryRegion {
    void *start;
    void *end;
} Mem_MemoryRegion;

extern void Mem_GetMemoryBlockRegion(Mem_MemoryRegion *region,
                                     Mem_ExpHeapMemoryBlock *block);
extern Mem_ExpHeapMemoryBlock *Mem_ExpHeapMemoryBlockList_Remove(
    Mem_ExpHeapMemoryBlockList *list, Mem_ExpHeapMemoryBlock *block);
extern Mem_ExpHeapMemoryBlock *Mem_Exp_InitializeMemoryBlock(
    Mem_MemoryRegion *region, u16 signature);
extern Mem_ExpHeapMemoryBlock *Mem_ExpHeapMemoryBlockList_Insert(
    Mem_ExpHeapMemoryBlockList *list, Mem_ExpHeapMemoryBlock *target,
    Mem_ExpHeapMemoryBlock *previous);
extern int Mem_Exp_CoalesceFreedRegion(Mem_ExpHeapHead *heap,
                                       Mem_MemoryRegion *region);
extern void MIi_CpuClear32(u32 value, void *destination, u32 size);

static inline void *AddU32ToPtr(void *pointer, u32 value)
{
    return (void *)((u32)pointer + value);
}

static inline void *SubU32ToPtr(void *pointer, u32 value)
{
    return (void *)((u32)pointer - value);
}

static inline u32 GetOffsetFromPtr(const void *start, const void *end)
{
    return (u32)end - (u32)start;
}

static inline void *GetMemPtrForMBlock(Mem_ExpHeapMemoryBlock *block)
{
    return AddU32ToPtr(block, sizeof(Mem_ExpHeapMemoryBlock));
}

static inline void *GetMBlockHeadPtr(void *block)
{
    return SubU32ToPtr(block, sizeof(Mem_ExpHeapMemoryBlock));
}

static inline void *GetMBlockEndAddr(Mem_ExpHeapMemoryBlock *block)
{
    return AddU32ToPtr(GetMemPtrForMBlock(block), block->block_size);
}

static inline Mem_ExpHeapHead *GetExpHeapHeadPtrFromHandle(Mem_HeapHead *heap)
{
    return AddU32ToPtr(heap, sizeof(Mem_HeapHead));
}

static inline u16 GetOptForHeap(const Mem_HeapHead *heap)
{
    return (u16)((heap->option >> 0) & ((1 << 8) - 1));
}

static inline void FillAllocMemory(Mem_HeapHead *heap, void *address, u32 size)
{
    if (GetOptForHeap(heap) & 1) {
        volatile u32 clear_value = 0;

        MIi_CpuClear32(clear_value, address, size);
    }
}

u32 Mem_ResizeExpHeap(Mem_HeapHead *heap, void *mem_block, u32 size)
{
    Mem_ExpHeapHead *exp_head;
    Mem_ExpHeapMemoryBlock *block_head;

    exp_head = GetExpHeapHeadPtrFromHandle(heap);
    block_head = GetMBlockHeadPtr(mem_block);
    size = (size + 3) & ~3;

    if (size == block_head->block_size) {
        return size;
    }

    if (size > block_head->block_size) {
        void *used_end = GetMBlockEndAddr(block_head);
        Mem_ExpHeapMemoryBlock *free_block;

        for (free_block = exp_head->free_list.head; free_block;
             free_block = free_block->next) {
            if (free_block == used_end) {
                break;
            }
        }

        if (!free_block ||
            size > block_head->block_size +
                       sizeof(Mem_ExpHeapMemoryBlock) +
                       free_block->block_size) {
            return 0;
        }

        Mem_MemoryRegion free_region;
        void *old_free_start;
        Mem_ExpHeapMemoryBlock *previous_free_block;

        Mem_GetMemoryBlockRegion(&free_region, free_block);
        previous_free_block = Mem_ExpHeapMemoryBlockList_Remove(
            &exp_head->free_list, free_block);
        old_free_start = free_region.start;
        free_region.start = AddU32ToPtr(mem_block, size);

        if (GetOffsetFromPtr(free_region.start, free_region.end) <
            sizeof(Mem_ExpHeapMemoryBlock)) {
            free_region.start = free_region.end;
        }

        block_head->block_size =
            GetOffsetFromPtr(mem_block, free_region.start);

        if (GetOffsetFromPtr(free_region.start, free_region.end) >=
            sizeof(Mem_ExpHeapMemoryBlock)) {
            Mem_ExpHeapMemoryBlockList_Insert(
                &exp_head->free_list,
                Mem_Exp_InitializeMemoryBlock(&free_region, 0x4652),
                previous_free_block);
        }

        FillAllocMemory(
            heap, old_free_start,
            GetOffsetFromPtr(old_free_start, free_region.start));
    } else {
        Mem_MemoryRegion free_region;
        const u32 old_block_size = block_head->block_size;

        free_region.start = AddU32ToPtr(mem_block, size);
        free_region.end = GetMBlockEndAddr(block_head);
        block_head->block_size = size;

        if (!Mem_Exp_CoalesceFreedRegion(exp_head, &free_region)) {
            block_head->block_size = old_block_size;
        }
    }

    return block_head->block_size;
}
