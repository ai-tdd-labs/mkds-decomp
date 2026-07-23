// PURPOSE: Creates, registers, and activates an animation.
// The first two arguments provide the source and target for the new animation.
// The third argument receives the allocated animation object; the final two
// arguments are probably creation and registration resources.

extern void *GetActiveExecutionContext(void);
extern int ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void Animation_CreateFrom(
    void *source, void *animation, void *target, int enabled, int heapHandle,
    void *createParam);
extern void Animation_RegisterAll(void *animation, void *registerParam, int heapHandle);
extern void Animation_SetAt(void *animation, int slot);

void func_020ea4bc(
    void *source, void *target, void **animation, void *createParam,
    void *registerParam)
{
    *animation = Mem_AllocateHeap(
        (void *)ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0x38);
    Animation_CreateFrom(
        source, *animation, target, 1,
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), createParam);
    Animation_RegisterAll(
        *animation, registerParam,
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()));
    Animation_SetAt(*animation, 0);
}
