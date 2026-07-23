// PURPOSE: Releases the dialog screen's heap.
// The global probably owns the dialog screen's allocated heap at offset 0x1a4.
// This destroys that heap and clears the global pointer afterward.

typedef struct DialogScreenWork {
    unsigned char padding_00[0x1a4];
    void *heap;
} DialogScreenWork;

extern DialogScreenWork *data_02174e64;
extern void Mem_DestroyHeap(void *heap);

void func_0203434c(void)
{
    Mem_DestroyHeap(data_02174e64->heap);
    data_02174e64 = 0;
}
