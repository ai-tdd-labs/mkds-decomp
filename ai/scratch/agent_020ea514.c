// PURPOSE: Loads an animation and makes it active.
// The first two inputs probably identify the animation source and its target.
// The third input is the animation object; the fourth and fifth are passed to
// its creation and registration helpers.

extern void *GetActiveExecutionContext(void);
extern int ExecutionContext_GetHeapHandle(void *context);
extern void Animation_CreateFrom(
    void *source, void *animation, void *target, int enabled, int heapHandle,
    void *createParam);
extern void Animation_RegisterAll(void *animation, void *registerParam, int heapHandle);
extern void Animation_SetAt(void *animation, int slot);

void SomeAnimationLoadWrapper_from_thumb(
    void *source, void *target, void *animation, void *createParam,
    void *registerParam)
{
    Animation_CreateFrom(
        source, animation, target, 1,
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), createParam);
    Animation_RegisterAll(
        animation, registerParam,
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()));
    Animation_SetAt(animation, 0);
}
