// PURPOSE: Allocates a small object and stores its setup values.
// The arguments are retained in the object for later use.
// The object is probably a callback or task record.

typedef struct AllocatedObject {
    int reserved0;
    int reserved4;
    void *arg0;
    int arg2;
    void *arg1;
    int state;
    int enabled;
} AllocatedObject;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);

void *func_0209bf1c(void *arg0, void *arg1, int arg2)
{
    AllocatedObject *object;

    object = (AllocatedObject *)Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0x2c);
    object->enabled = 1;
    object->arg0 = arg0;
    object->arg2 = arg2;
    object->arg1 = arg1;
    object->state = 0;
    return object;
}
