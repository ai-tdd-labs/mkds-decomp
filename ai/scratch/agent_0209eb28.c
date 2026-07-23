// PURPOSE: Creates an empty game object.
// This wrapper passes no callbacks or configuration to the object allocator.
// The returned object is probably initialized entirely by the allocator.

extern void *CreateAllocateSomeObject_from_thumb(void *cb1, void *cb2,
                                                   void *cb3, int a4, int a5);

void func_0209eb28(void)
{
    // PURPOSE: Creates an empty game object.
    CreateAllocateSomeObject_from_thumb(0, 0, 0, 0, 0);
}
