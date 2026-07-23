// PURPOSE: Creates data for the kart appearance table.
// The heap argument provides memory for the new data.
// It probably loads the appearance table pointer and initializes the result.

typedef struct KartAppearTableData {
    char padding[0x44];
    void **appearTable;
} KartAppearTableData;

extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void **LoadKartAppearTablePointer_from_thumb(void *heap);
extern void StructKTB_SomeFn_from_thumb(void *data);

void *AllocateKartAppearTableData_from_thumb(void *heap)
{
    KartAppearTableData *data =
        (KartAppearTableData *)Mem_AllocateHeap(heap, 0x48);

    data->appearTable = LoadKartAppearTablePointer_from_thumb(heap);
    StructKTB_SomeFn_from_thumb(data);

    return data;
}
