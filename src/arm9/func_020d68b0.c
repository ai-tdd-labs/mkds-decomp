/*
PURPOSE: Creates a configured 64-byte object from a shared template.
The function allocates the object from the active execution context's heap.
It copies the template, then sets the final two fields to opposite fixed bounds.
It takes no arguments and returns the newly allocated object.
*/

typedef unsigned int u32;
typedef int s32;

typedef struct ConfiguredObject {
    u32 templateFields[14];
    s32 upperBound;
    s32 lowerBound;
} ConfiguredObject;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern const ConfiguredObject data_02156adc;

void *func_020d68b0(void)
{
    ConfiguredObject *object = (ConfiguredObject *)Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0x40);

    *object = data_02156adc;
    object->upperBound = 0x3e8000;
    object->lowerBound = -0x3e8000;
    return object;
}
