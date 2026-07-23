// PURPOSE: Creates an object with two behavior callbacks.
//
// The allocator receives the setup and update callbacks, no third callback,
// and two enabled flags. The allocated object is intentionally not retained
// here because the allocator probably registers it internally.

extern void func_020a7fc4(void);
extern void func_020a7f18(void);
extern void *CreateAllocateSomeObject_from_thumb(void *cb1, void *cb2, void *cb3, int a4, int a5);

void func_020a737c(void)
{
    CreateAllocateSomeObject_from_thumb((void *)func_020a7fc4, (void *)func_020a7f18, 0, 1, 1);
}
