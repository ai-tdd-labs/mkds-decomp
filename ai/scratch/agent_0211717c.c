// PURPOSE: Creates storage for the kart appearance table.
// The heap supplies the memory for a pointer holder.
// The holder then receives the table data, probably for later kart setup.

extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void *AllocateKartAppearTableData_from_thumb(void *heap);
extern void **data_0217d358;

void CreateSetGlobalKTB_from_thumb(void *heap)
{
    data_0217d358 = Mem_AllocateHeap(heap, 4);
    *data_0217d358 = AllocateKartAppearTableData_from_thumb(heap);
}
