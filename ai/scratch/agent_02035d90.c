// PURPOSE: Releases the current screen's heap.
// The global probably owns a work object with its heap pointer at offset 0x1a4.
// It destroys that heap and clears the global work pointer afterward.

typedef struct ScreenWork {
    unsigned char padding_00[0x1a4];
    void *heap;
} ScreenWork;

extern ScreenWork *data_02174e6c;
extern void Mem_DestroyHeap(void *heap);

void func_02035d90(void)
{
    Mem_DestroyHeap(data_02174e6c->heap);
    data_02174e6c = 0;
}
