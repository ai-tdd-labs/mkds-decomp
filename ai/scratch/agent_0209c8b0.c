/* PURPOSE: Tells another system whether this object just finished, choosing
 * between a scaled or unscaled speed value depending on a couple of flags.
 *
 * arg0 is a pointer to an object; arg1..arg3 are simply forwarded to
 * func_020ead80 (probably a "finish"/"end" notification call). If bit
 * 0x800 of the flags at +0x2 is clear AND the mode field at +0x11c is 1,
 * the value at +0x58 is scaled by the fixed-point (12.20) factor at +0xbc
 * before being passed on; otherwise the raw value at +0x58 is used.
 * The result of func_020ead80 is cached at +0xa4 and the function returns
 * 1 if that result is non-zero, 0 otherwise.
 */
extern int func_020ead80(int a0, void *a1, void *a2, int a3, int a4, int a5,
                          int a6, int a7);

int func_0209c8b0(void *arg0, int arg1, int arg2, int arg3)
{
    unsigned char *b = (unsigned char *)arg0;

    if (!(*(unsigned short *)(b + 2) & 0x800) && *(int *)(b + 0x11c) == 1) {
        /* fixed-point (12.20) multiply, keep only the low 32 bits of the
         * 64-bit product shifted right by 12 */
        long long prod = (long long)*(int *)(b + 0x58) * (long long)*(int *)(b + 0xbc);
        int r3val = (int)(prod >> 12);

        *(int *)(b + 0xa4) = func_020ead80(arg1, (void *)(b + 4), (void *)(b + 0x28),
                                            r3val, *(int *)(b + 0x5c), 0, arg2, arg3);
    } else {
        *(int *)(b + 0xa4) = func_020ead80(arg1, (void *)(b + 4), (void *)(b + 0x28),
                                            *(int *)(b + 0x58), *(int *)(b + 0x5c), 0,
                                            arg2, arg3);
    }

    return *(int *)(b + 0xa4) != 0 ? 1 : 0;
}
