/*
PURPOSE: Initializes the shared scene overlay settings.

The argument is the heap used for the new 16-byte configuration record.
The function starts the overlay state at zero, sets the requested state to
the idle value three, and clears the probably optional audio buffer pointer.
*/

typedef unsigned int u32;

typedef struct SceneOverlayConfig {
    int overlayState;
    int requestedState;
    int unknown_08;
    void *audioBuffer;
} SceneOverlayConfig;

extern void *Mem_AllocateHeap(void *heap, u32 size);
extern SceneOverlayConfig *data_0217aa20;

void InitializeSceneOverlayConfig(void *heap)
{
    data_0217aa20 = (SceneOverlayConfig *)Mem_AllocateHeap(heap, 0x10);
    data_0217aa20->overlayState = 0;
    data_0217aa20->requestedState = 3;
    data_0217aa20->audioBuffer = 0;
}
