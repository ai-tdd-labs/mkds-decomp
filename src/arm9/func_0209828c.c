/*
PURPOSE: Initialize a global state object and return it.

Loads two function/data pointers from the pool, calls an initialization function
with them and a zero argument, stores the result in a global data slot, calls
a second function with the global slot address, and returns the stored value.
*/

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;

// Declare these as arrays to avoid dereferencing when used as addresses
extern char func_0209886c[];
extern char func_020983c4[];
extern void *func_0209bf48(void *a, void *b, int c);
extern void func_020e6f50(void *ptr);
extern void *data_0217b0fc;

void *func_0209828c(void)
{
    void *result;

    result = func_0209bf48(func_0209886c, func_020983c4, 0);
    *(void**)&data_0217b0fc = result;
    func_020e6f50(&data_0217b0fc);

    return *(void**)&data_0217b0fc;
}
