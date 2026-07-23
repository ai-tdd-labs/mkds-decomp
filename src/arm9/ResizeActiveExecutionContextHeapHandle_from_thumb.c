// PURPOSE: Resizes the active execution context heap allocation.
// The first argument is the allocation start and the second extends its end.
// It probably uses the shared archive heap as the allocation base.

extern char *data_021759c8;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void Mem_ResizeExpHeap(void *heap, void *start, unsigned int size);

void ResizeActiveExecutionContextHeapHandle_from_thumb(void *start,
                                                       unsigned int endOffset)
{
    void *base = *(void **)(data_021759c8 + 0x84c);

    Mem_ResizeExpHeap(ExecutionContext_GetHeapHandle(GetActiveExecutionContext()),
                      base, (unsigned int)start - (unsigned int)base + endOffset);
}
