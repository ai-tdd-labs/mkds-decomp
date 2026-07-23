// PURPOSE: Creates the memory used to hold save data.
// Argument: heap is the heap that owns the save-data allocations.
// Behaviour: allocates the save-data holder and its ten aligned section buffers,
// then clears their contents and initializes the holder's status fields.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct SaveDataHolder {
    void *section0;
    void *section1;
    void *section2;
    void *section3;
    void *section4;
    void *section5;
    void *section6;
    void *section7;
    void *section8;
    void *section9;
    u8 state;
    u8 pad_29;
    u16 value_2a;
    u32 value_2c;
    u8 pad_30[0x10];
    u32 value_40;
    u32 flags_44;
} SaveDataHolder;

extern SaveDataHolder *data_0217aa08;

extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void *Mem_AllocateHeapAligned(void *heap, unsigned int size,
                                    unsigned int alignment);
extern void ClearAllSaveDataSections_from_thumb(int arg0);

void InitializeSaveDataHolder_from_thumb(void *heap)
{
    data_0217aa08 = Mem_AllocateHeap(heap, 0x48);

    data_0217aa08->section0 = Mem_AllocateHeapAligned(heap, 0x100, 0x20);
    data_0217aa08->section1 = Mem_AllocateHeapAligned(heap, 0x300, 0x20);
    data_0217aa08->section2 = Mem_AllocateHeapAligned(heap, 0x400, 0x20);
    data_0217aa08->section3 = Mem_AllocateHeapAligned(heap, 0x1600, 0x20);
    data_0217aa08->section4 = Mem_AllocateHeapAligned(heap, 0x100, 0x20);
    data_0217aa08->section5 = Mem_AllocateHeapAligned(heap, 0xe00, 0x20);
    data_0217aa08->section6 = Mem_AllocateHeapAligned(heap, 0x1000, 0x20);
    data_0217aa08->section7 = Mem_AllocateHeapAligned(heap, 0x1000, 0x20);
    data_0217aa08->section8 = Mem_AllocateHeapAligned(heap, 0xc00, 0x20);
    data_0217aa08->section9 = Mem_AllocateHeapAligned(heap, 0xb00, 0x20);
    data_0217aa08->value_40 = 0;

    ClearAllSaveDataSections_from_thumb(1);

    data_0217aa08->value_2a = 0;
    data_0217aa08->value_2c = 0;
    data_0217aa08->flags_44 &= ~1;
    data_0217aa08->state = 0;
}
