/*
PURPOSE: Sets up two sound/system work buffers on the given heap.
Argument is a heap pointer. Queries two required buffer sizes (with
parameter 0x20), allocates both buffers from the heap, then registers
each with its subsystem: the first with func_02017070 (ids 0x40000 and
0x20000, flag 1), the second with func_02017274 (id 0x10000, flag 1).
The 0x40000/0x20000/0x10000 constants are literal pool words (no reloc).
*/

extern unsigned int ComputeSomeAllocSize_0(int param);
extern unsigned int ComputeSomeAllocSize_1(int param);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void func_02017070(int a, int b, void *buf, unsigned int size, int flag);
extern void func_02017274(int a, void *buf, unsigned int size, int flag);

void func_02077bc0(void *heap)
{
    unsigned int size0;
    unsigned int size1;
    void *buf0;
    void *buf1;

    size0 = ComputeSomeAllocSize_0(0x20);
    size1 = ComputeSomeAllocSize_1(0x20);
    buf0 = Mem_AllocateHeap(heap, size0);
    buf1 = Mem_AllocateHeap(heap, size1);
    func_02017070(0x40000, 0x20000, buf0, size0, 1);
    func_02017274(0x10000, buf1, size1, 1);
}
