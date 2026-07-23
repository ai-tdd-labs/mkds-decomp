/* PURPOSE: Initializes a kart-select resource slot.
 * The heap supplies five resource and work allocations for the slot.
 * The function also initializes its shared model state, copies a probably
 * system-wide value, and clears the adjacent status field.
 */

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct StructCESub {
    u8 inheritedState[0x08];
    void *workBlock38;       /* 0x08 */
    u8 unknown_0c[0x04];
    void *resourceBlock0;    /* 0x10 */
    void *resourceBlock1;    /* 0x14 */
    void *resourceBlock2;    /* 0x18 */
    void *extendedBlock;     /* 0x1c */
    u8 unknown_20[0x90];
    u32 sharedSystemValue;   /* 0xb0: exact meaning is uncertain */
    u32 status;              /* 0xb4 */
} StructCESub;

typedef struct SystemContext {
    u32 sharedValue;
} SystemContext;

extern void StructAD00Sub_Initialize_from_thumb(StructCESub *sub);
extern void *Mem_AllocateHeap(void *heap, u32 size);
extern SystemContext *data_021759d0;

void StructCESub_Initialize_from_thumb(void *heap, StructCESub *sub)
{
    StructAD00Sub_Initialize_from_thumb(sub);
    sub->sharedSystemValue = data_021759d0->sharedValue;
    sub->status = 0;

    sub->resourceBlock0 = Mem_AllocateHeap(heap, 0x6c);
    sub->resourceBlock1 = Mem_AllocateHeap(heap, 0x6c);
    sub->resourceBlock2 = Mem_AllocateHeap(heap, 0x6c);
    sub->extendedBlock = Mem_AllocateHeap(heap, 0x74);
    sub->workBlock38 = Mem_AllocateHeap(heap, 0x38);
}
