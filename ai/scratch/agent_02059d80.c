// PURPOSE: Releases the overlay manager's heap.
// The manager probably owns an expandable heap at offset 0xA4.
// It does nothing when that heap has not been created yet.

typedef struct OverlayManager {
    unsigned char padding_00[0xA4];
    void *heap;
} OverlayManager;

extern OverlayManager *data_0217aa10;
extern void Mem_Exp_Finalize(void *heap);

void DisposeOverlayManagerHeap(void)
{
    if (data_0217aa10->heap == 0) {
        return;
    }

    Mem_Exp_Finalize(data_0217aa10->heap);
    data_0217aa10->heap = 0;
}
