// PURPOSE: Allocates and initializes shared pointer tables.
// The active execution context supplies the heap for seven global buffers.
// One table receives identifiers from 1 through 256.
// Another probably stores records whose pointer field starts empty.

typedef short s16;
typedef unsigned short u16;

typedef struct PointerRecord {
    unsigned char field_00[0xc];
    void *field_0c;
    unsigned char field_10[0xc];
} PointerRecord;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);

extern u16 data_0217b5ac;
extern u16 data_0217b5b0;
extern void *data_0217b5b4;
extern PointerRecord *volatile data_0217b5b8;
extern void *data_0217b5bc;
extern void *data_0217b5c0;
extern void *data_0217b5c4;
extern u16 *volatile data_0217b5c8;
extern void *data_0217b5cc;

void AllocateSomePointers(void)
{
    void *heap;
    s16 i;
    s16 j;

    heap = ExecutionContext_GetHeapHandle(GetActiveExecutionContext());

    data_0217b5b0 = 0;
    data_0217b5ac = 0;
    data_0217b5b4 = Mem_AllocateHeap(heap, 0x400);
    data_0217b5c0 = Mem_AllocateHeap(heap, 0x400);
    data_0217b5b8 = Mem_AllocateHeap(heap, 0x1c00);
    data_0217b5c8 = Mem_AllocateHeap(heap, 0x200);
    data_0217b5cc = Mem_AllocateHeap(heap, 0x100);
    data_0217b5bc = Mem_AllocateHeap(heap, 0x100);
    data_0217b5c4 = Mem_AllocateHeap(heap, 0x200);

    i = 0;
    do {
        data_0217b5c8[i] = ++i;
    } while (i < 0x100);

    for (j = 0; j < 0x100; j++) {
        data_0217b5b8[j].field_0c = 0;
    }
}
