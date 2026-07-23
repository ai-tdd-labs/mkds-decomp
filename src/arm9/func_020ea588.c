// PURPOSE: Creates a model object from supplied model data.
// The first argument receives a newly allocated 0x6c-byte model object.
// The second argument probably points to NSBMD model data used to initialize it.

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void Model_CreateFromNsbmd(void *model, void *nsbmd);

void func_020ea588(void **out_model, void *nsbmd)
{
    *out_model = Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0x6C);
    Model_CreateFromNsbmd(*out_model, nsbmd);
}
