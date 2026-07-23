// PURPOSE: Creates an object with the default empty callbacks.
// Passes three null callback slots, an enabled flag, and a null extra value
// to the object allocator. The returned object is probably intentionally
// ignored because this wrapper only triggers creation.

extern void *CreateAllocateSomeObject_from_thumb(void *cb1, void *cb2, void *cb3, int enabled, int extra);

void func_020ac67c(void)
{
    CreateAllocateSomeObject_from_thumb(0, 0, 0, 1, 0);
}
