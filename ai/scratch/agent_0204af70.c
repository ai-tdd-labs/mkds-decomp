/* PURPOSE: Creates the main system context and its memory arena.
 * The argument is the heap used to allocate the context object.
 * Region 4 supplies the arena memory, then the remaining context fields are populated.
 */

typedef unsigned int u32;

typedef struct SystemContext {
    unsigned char unknown_00[0x24];
    void *memoryArena;
} SystemContext;

extern void *Os_GetMemoryRegionStartAddress(int region);
extern void *Os_GetMemoryRegionEndAddress(int region);
extern void *Mem_AllocateHeap(void *heap, u32 size);
extern void *Mem_Frame_Create(void *start, u32 size, int direction);
extern void PopulateSystemContext(void);

extern SystemContext *data_021759d0;

void InitializeSystemContext(void *heap)
{
    void *regionStart = Os_GetMemoryRegionStartAddress(4);
    void *regionEnd = Os_GetMemoryRegionEndAddress(4);

    data_021759d0 = (SystemContext *)Mem_AllocateHeap(heap, 0x7c);
    data_021759d0->memoryArena = Mem_Frame_Create(
        regionStart, (u32)regionEnd - (u32)regionStart, 1);
    PopulateSystemContext();
}
