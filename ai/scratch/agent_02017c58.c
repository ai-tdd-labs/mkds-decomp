// PURPOSE: Converts part of a free heap block into an allocated block.
// The heap, free block, requested address, size, and direction define the allocation.
// Any regions large enough to remain free are returned to the free-block list.
// The allocated block records its direction, alignment, and the heap's current group.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Mem_MemoryRegion {
    void *start;
    void *end;
} Mem_MemoryRegion;

typedef struct Mem_ExpHeapMemoryBlockHead Mem_ExpHeapMemoryBlockHead;

struct Mem_ExpHeapMemoryBlockHead {
    u16 signature;
    u16 attribute;
    u32 block_size;
    Mem_ExpHeapMemoryBlockHead *previous;
    Mem_ExpHeapMemoryBlockHead *next;
};

typedef struct Mem_ExpHeapMemoryBlockList {
    Mem_ExpHeapMemoryBlockHead *head;
    Mem_ExpHeapMemoryBlockHead *tail;
} Mem_ExpHeapMemoryBlockList;

typedef struct Mem_ExpHeapHead {
    Mem_ExpHeapMemoryBlockList free_list;
    Mem_ExpHeapMemoryBlockList used_list;
    u16 group_id;
    u16 feature;
} Mem_ExpHeapHead;

typedef struct Mem_HeapHead {
    u8 padding[0x20];
    u32 option;
} Mem_HeapHead;

extern void Mem_GetMemoryBlockRegion(
    Mem_MemoryRegion *region,
    Mem_ExpHeapMemoryBlockHead *block);
extern Mem_ExpHeapMemoryBlockHead *Mem_ExpHeapMemoryBlockList_Remove(
    Mem_ExpHeapMemoryBlockList *list,
    Mem_ExpHeapMemoryBlockHead *block);
extern Mem_ExpHeapMemoryBlockHead *Mem_Exp_InitializeMemoryBlock(
    const Mem_MemoryRegion *region,
    u16 signature);
extern Mem_ExpHeapMemoryBlockHead *Mem_ExpHeapMemoryBlockList_Insert(
    Mem_ExpHeapMemoryBlockList *list,
    Mem_ExpHeapMemoryBlockHead *target,
    Mem_ExpHeapMemoryBlockHead *previous);
extern void MIi_CpuClear32(u32 value, void *destination, u32 size);

static inline u32 Mem_GetOffsetFromPointer(
    const void *start,
    const void *end)
{
    return (u32)end - (u32)start;
}

static inline void *Mem_AddToPointer(void *pointer, u32 amount)
{
    return (void *)((u32)pointer + amount);
}

static inline void *Mem_SubtractFromPointer(void *pointer, u32 amount)
{
    return (void *)((u32)pointer - amount);
}

static inline Mem_HeapHead *Mem_GetHeapHeadFromExpHeapHead(
    Mem_ExpHeapHead *exp_heap_head)
{
    return Mem_SubtractFromPointer(exp_heap_head, sizeof(Mem_HeapHead));
}

static inline u16 Mem_GetHeapOption(const Mem_HeapHead *heap_head)
{
    return (u16)((heap_head->option >> 0) & ((1 << 8) - 1));
}

static inline void Mem_FillAllocatedMemory(
    Mem_HeapHead *heap_head,
    void *address,
    u32 size)
{
    if (Mem_GetHeapOption(heap_head) & 1) {
        volatile u32 fill_value = 0;

        MIi_CpuClear32(fill_value, address, size);
    }
}

#define Mem_SetBitValue(data, start, bits, value) do { \
    u32 mask = (u32)((1 << (bits)) - 1);               \
    u32 new_value = (value) & mask;                    \
    (void)(mask <<= (start));                          \
    (data) &= ~mask;                                   \
    (data) |= new_value << (start);                    \
} while (0)

static inline void Mem_SetBlockAllocationDirection(
    Mem_ExpHeapMemoryBlockHead *block,
    u16 direction)
{
    Mem_SetBitValue(block->attribute, 15, 1, direction);
}

static inline void Mem_SetBlockAlignment(
    Mem_ExpHeapMemoryBlockHead *block,
    u16 alignment)
{
    Mem_SetBitValue(block->attribute, 8, 7, alignment);
}

static inline void Mem_SetBlockGroupId(
    Mem_ExpHeapMemoryBlockHead *block,
    u16 group_id)
{
    Mem_SetBitValue(block->attribute, 0, 8, group_id);
}

static inline Mem_ExpHeapMemoryBlockHead *Mem_InitializeFreeBlock(
    const Mem_MemoryRegion *region)
{
    return Mem_Exp_InitializeMemoryBlock(region, 0x4652);
}

static inline void Mem_AppendMemoryBlock(
    Mem_ExpHeapMemoryBlockList *list,
    Mem_ExpHeapMemoryBlockHead *block)
{
    (void)Mem_ExpHeapMemoryBlockList_Insert(list, block, list->tail);
}

void *Mem_Exp_ConvertFreeBlockToUsedBlock(
    Mem_ExpHeapHead *exp_heap_head,
    Mem_ExpHeapMemoryBlockHead *free_block,
    void *memory,
    u32 size,
    u16 allocation_direction)
{
    Mem_MemoryRegion free_region_before;
    Mem_MemoryRegion free_region_after;
    Mem_ExpHeapMemoryBlockHead *previous_free_block;

    Mem_GetMemoryBlockRegion(&free_region_before, free_block);

    free_region_after.end = free_region_before.end;
    free_region_after.start = Mem_AddToPointer(memory, size);
    free_region_before.end =
        Mem_SubtractFromPointer(memory, sizeof(Mem_ExpHeapMemoryBlockHead));

    previous_free_block = Mem_ExpHeapMemoryBlockList_Remove(
        &exp_heap_head->free_list,
        free_block);

    if (Mem_GetOffsetFromPointer(
            free_region_before.start,
            free_region_before.end) <
        sizeof(Mem_ExpHeapMemoryBlockHead)) {
        free_region_before.end = free_region_before.start;
    } else {
        previous_free_block = Mem_ExpHeapMemoryBlockList_Insert(
            &exp_heap_head->free_list,
            Mem_InitializeFreeBlock(&free_region_before),
            previous_free_block);
    }

    if (Mem_GetOffsetFromPointer(
            free_region_after.start,
            free_region_after.end) <
        sizeof(Mem_ExpHeapMemoryBlockHead)) {
        free_region_after.start = free_region_after.end;
    } else {
        (void)Mem_ExpHeapMemoryBlockList_Insert(
            &exp_heap_head->free_list,
            Mem_InitializeFreeBlock(&free_region_after),
            previous_free_block);
    }

    Mem_FillAllocatedMemory(
        Mem_GetHeapHeadFromExpHeapHead(exp_heap_head),
        free_region_before.end,
        Mem_GetOffsetFromPointer(
            free_region_before.end,
            free_region_after.start));

    {
        Mem_ExpHeapMemoryBlockHead *used_block;
        Mem_MemoryRegion used_region;

        used_region.start = Mem_SubtractFromPointer(
            memory,
            sizeof(Mem_ExpHeapMemoryBlockHead));
        used_region.end = free_region_after.start;

        used_block = Mem_Exp_InitializeMemoryBlock(&used_region, 0x5544);
        Mem_SetBlockAllocationDirection(used_block, allocation_direction);
        Mem_SetBlockAlignment(
            used_block,
            (u16)Mem_GetOffsetFromPointer(
                free_region_before.end,
                used_block));
        Mem_SetBlockGroupId(used_block, exp_heap_head->group_id);
        Mem_AppendMemoryBlock(&exp_heap_head->used_list, used_block);
    }

    return memory;
}
