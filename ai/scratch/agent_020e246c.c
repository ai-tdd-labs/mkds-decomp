// PURPOSE: Updates an object from a target position when its mode byte is one.
// Takes an object pointer, a base pointer, a mode-byte pointer, and a result-byte pointer.
// It probably updates the object using the target stored at base offset 0x50.

typedef unsigned char u8;
typedef unsigned int u32;

extern void func_020e24d0(void *object, const void *target);

u32 func_020e246c(void *object, void *base, u8 *mode, u8 *result)
{
    if (*mode == 1) {
        func_020e24d0(object, (u8 *)base + 0x50);
    }
    return *result;
}
