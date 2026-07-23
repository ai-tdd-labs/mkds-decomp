// PURPOSE: Sets up the manager for loadable overlay memory.
// The caller provides the heap used to allocate the manager.
// Three overlay regions are recorded and their shared address bounds are found.

typedef unsigned int u32;

typedef struct OverlayRegion {
    u32 overlay_index;
    void *start_address;
    void *end_address;
} OverlayRegion;

typedef struct OverlayManager {
    u32 current_overlay;
    u32 state;
    OverlayRegion regions[3];
    unsigned char padding_2c[0x74];
    void *frame_heap;
    void *region_heap;
    u32 lowest_address;
    u32 highest_address;
} OverlayManager;

extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern OverlayManager *data_0217aa10;

void InitializeOverlayManager(void *heap)
{
    OverlayRegion *region;

    data_0217aa10 = (OverlayManager *)Mem_AllocateHeap(heap, 0xb0);
    data_0217aa10->lowest_address = (u32)-1;
    data_0217aa10->highest_address = 0;

    region = &data_0217aa10->regions[0];
    *region = (OverlayRegion){0, (void *)0x021804e0, (void *)0x021b7ba0};
    if ((u32)region->start_address < data_0217aa10->lowest_address) {
        data_0217aa10->lowest_address = (u32)region->start_address;
    }
    if ((u32)region->end_address > data_0217aa10->highest_address) {
        data_0217aa10->highest_address = (u32)region->end_address;
    }

    region = &data_0217aa10->regions[1];
    *region = (OverlayRegion){1, (void *)0x021804e0, (void *)0x021ca440};
    if ((u32)region->start_address < data_0217aa10->lowest_address) {
        data_0217aa10->lowest_address = (u32)region->start_address;
    }
    if ((u32)region->end_address > data_0217aa10->highest_address) {
        data_0217aa10->highest_address = (u32)region->end_address;
    }

    region = &data_0217aa10->regions[2];
    *region = (OverlayRegion){2, (void *)0x021804e0, (void *)0x021d0500};
    if ((u32)region->start_address < data_0217aa10->lowest_address) {
        data_0217aa10->lowest_address = (u32)region->start_address;
    }
    if ((u32)region->end_address > data_0217aa10->highest_address) {
        data_0217aa10->highest_address = (u32)region->end_address;
    }

    data_0217aa10->frame_heap = 0;
    data_0217aa10->region_heap = 0;
}
