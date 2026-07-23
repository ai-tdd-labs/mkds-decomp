// PURPOSE: Clears the twelve shared transition slots.
// Each slot is initialized while its consecutive object identifier is removed
// from the global list, then the shared transition state is cleared.

typedef unsigned short u16;

typedef struct GlobalGO {
    void *object;
    char unknown_04[0x24];
    struct GlobalGO *next;
} GlobalGO;

extern void *data_0217aa00;
extern GlobalGO *func_02006df8(void *object);

void func_0204ee64(void)
{
    int i = 0;
    int offset = i;
    int zero = i;

    do {
        func_02006df8((void *)(u16)(i + 1000));
        *(int *)((char *)data_0217aa00 + offset + 0x1714) = zero;
        offset += 0x88;
        i++;
    } while (i < 12);

    *(u16 *)((char *)data_0217aa00 + 0x1e40) = (u16)zero;
}
