// PURPOSE: Allocates and initializes the shared scene work record.
// The supplied heap provides a 0x1f00-byte, 32-byte-aligned allocation.
// The record's exact scene role is probably related to transitions or wireless state.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct GlobalZE {
    int state;
    int unk4;
    int unk8;
    int request;
    int busy;
    u8 pad_14[0x440];
    u16 handle;
    u8 flags;
} GlobalZE;

extern void *Mem_AllocateHeapAligned(void *heap, u32 size, u32 alignment);
extern GlobalZE *data_0217aa00;

void InitializeGlobalZE(void *heap)
{
    data_0217aa00 = (GlobalZE *)Mem_AllocateHeapAligned(heap, 0x1f00, 0x20);
    data_0217aa00->state = 0;
    data_0217aa00->unk4 = 0;
    data_0217aa00->unk8 = 9;
    data_0217aa00->request = 0;
    data_0217aa00->busy = 0;
    data_0217aa00->handle = 0;
    data_0217aa00->flags &= (u8)~1;
}
