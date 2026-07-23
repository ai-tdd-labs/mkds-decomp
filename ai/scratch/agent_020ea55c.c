// PURPOSE: Allocates and initializes a small runtime object.
// The output pointer receives a 0x74-byte heap allocation.
// The allocation is probably initialized using the supplied data and byte flag.

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void StructAD00Sh_SomeFn_2(void *object, void *data, int flag);

void func_020ea55c(void **out_object, void *data, int flag)
{
    int saved_flag = flag;
    void *saved_data = data;

    *out_object = Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0x74);
    StructAD00Sh_SomeFn_2(*out_object, saved_data, (unsigned char)saved_flag);
}
