/*
 * PURPOSE: Sets up a newly allocated race object using data copied from a source descriptor.
 *
 * a1: pointer to a source descriptor; word 0 is a container pointer and halfword 8 is a
 *     small id, both copied into the new object.
 * a2: an opaque id (probably owner/player index) stored into the new object and also
 *     forwarded to func_02100138.
 *
 * First calls func_02100138 (probably releases/prepares a previous instance), then
 * fetches a fresh object via func_0209bbfc(). If none is available the function does
 * nothing. Otherwise it clears a few flag bits, copies fields from a1, sets a fixed
 * scale, calls func_020d90a8() to finish base setup, computes a fixed-point-scaled
 * value from an array entry reached through the container pointer, and finally calls
 * func_0208b7bc() to initialize a sub-object embedded at offset 4.
 */

extern void func_02100138(int a0, int a1);
extern void *func_0209bbfc(void);
extern void func_020d90a8(void *slot, int a1, int a2);
extern int func_0208b7bc(int a0, void *a1);

void func_02098f18(void *a1, int a2)
{
    unsigned char *src = (unsigned char *)a1;
    unsigned char *p;
    unsigned char *destSlot;
    unsigned short flags;

    func_02100138(0x1ab, a2);
    p = (unsigned char *)func_0209bbfc();
    if (p == 0) {
        return;
    }

    destSlot = p + 0xa0;

    flags = *(unsigned short *)(p + 2);
    flags &= ~1;
    *(unsigned short *)(p + 2) = flags;

    flags = *(unsigned short *)(p + 2);
    flags &= ~8;
    *(unsigned short *)(p + 2) = flags;

    flags = *(unsigned short *)(p + 2);
    flags &= ~2;
    *(unsigned short *)(p + 2) = flags;

    flags = *(unsigned short *)(p + 2);
    flags &= ~8;
    *(unsigned short *)(p + 2) = flags;

    *(unsigned short *)(p + 0x66) = 0x1f;
    *(unsigned short *)(p + 0xa8) = *(unsigned short *)(src + 8);
    *(unsigned int *)(p + 0xa0) = *(unsigned int *)(src + 0);

    func_020d90a8(destSlot, 0, 1);

    *(unsigned int *)(p + 0xa4) = 0x7800;

    {
        unsigned char *container = *(unsigned char **)(p + 0xa0);
        unsigned int idx = *(unsigned int *)(p + 0xac);
        unsigned char *arrayBase = *(unsigned char **)container;
        int v = *(int *)(arrayBase + idx * 0x54 + 0x34);
        long long prod = (long long)v * 0x7800;
        *(unsigned int *)(p + 0xb0) = (unsigned int)(prod >> 12);
    }

    *(unsigned int *)(p + 0xc4) = a2;
    *(unsigned int *)(p + 0xc8) = -0x5000;
    *(unsigned int *)(p + 0xcc) = 0;

    *(unsigned int *)(p + 0xd0) = (unsigned int)func_0208b7bc(0x33, p + 4);
}
