// PURPOSE: Allocates and initializes a billboard model from model and animation data.
// Stores the new model through dst, then initializes it with the supplied resources.
// The final argument probably supplies optional animation configuration.

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void BillboardModel_CreateFromNsbmdNsbtp_from_thumb(
    void *model, void *nsbmd, void *nsbtp, void *config);

void BillboardModel_AllocateFromNsbmdNsbtp_from_thumb(
    void **dst, void *nsbmd, void *nsbtp, void *config)
{
    *dst = Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0x2c);
    BillboardModel_CreateFromNsbmdNsbtp_from_thumb(*dst, nsbmd, nsbtp, config);
}
