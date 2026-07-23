// PURPOSE: Allocates and initializes a small callback object.
// The three arguments are stored in the new object.
// The final field is cleared before the object is returned.

typedef struct CallbackObject {
    int reserved0;
    int reserved4;
    void *arg0;
    int arg2;
    void *arg1;
    int state;
} CallbackObject;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);

void *func_0209bf48(void *arg0, void *arg1, int arg2)
{
    CallbackObject *object;

    object = (CallbackObject *)Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0x28);
    object->arg0 = arg0;
    object->arg2 = arg2;
    object->arg1 = arg1;
    object->state = 0;
    return object;
}
