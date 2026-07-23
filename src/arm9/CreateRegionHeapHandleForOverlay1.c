// PURPOSE: Creates the overlay region heap once.
// The shared system context probably tracks whether this heap already exists.
// A fixed memory region is used for the heap and its handle is stored in that context.

typedef unsigned int u32;

typedef struct {
    char padding[0xa4];
    void *region_heap;
} SystemContext;

extern void *data_0217aa10;
extern void *Mem_Exp_Create(void *start, u32 size, int direction);

void CreateRegionHeapHandleForOverlay1(void) {
    if (*(int *)data_0217aa10 != 1) {
        return;
    }

    ((SystemContext *)data_0217aa10)->region_heap =
        Mem_Exp_Create((void *)0x021a9c00, 0x20800, 1);
}
