/*
 * PURPOSE: Copies one tuned value from a data block into a game object,
 *          picking a different value/slot depending on a mode flag.
 *
 * Args: a = target object, b = source data block, mode = which variant.
 * When mode == 0: calls a setup helper with one pair of constants, then
 *   scales source field b->fc4 by a Q12 fixed-point factor (0xB33/4096,
 *   rounded) and stores the 16-bit result into a->f5c.
 * When mode != 0: calls the setup helper with a different constant pair,
 *   copies the low 16 bits of b->fc4 into a->f6c, then sets bit 3 of the
 *   a->f24 flags word when b's flags (b->f7c) have bit0 clear AND any of
 *   the 0x402000 bits set (probably an "enabled/active" condition).
 */

typedef short s16;

typedef struct {
    char _p0[0x24];
    unsigned int f24_lo : 3;   /* 0x24 bits 0-2 */
    unsigned int f24_b3 : 1;   /* 0x24 bit 3 (the flag written here) */
    unsigned int f24_hi : 28;  /* 0x24 bits 4-31 */
    char _p28[0x5c - 0x28];
    int f5c;        /* 0x5c scaled value (mode 0) */
    char _p60[0x6c - 0x60];
    int f6c;        /* 0x6c raw value (mode != 0) */
} Foo;

typedef struct {
    char _p0[0x7c];
    int f7c;        /* 0x7c flags */
    char _p80[0xc4 - 0x80];
    int fc4;        /* 0xc4 source field */
} Bar;

extern void func_02081b64(Foo *a, Bar *b, int c0, int c1);

void func_02081ca0(Foo *a, Bar *b, int mode)
{
    if (mode == 0) {
        func_02081b64(a, b, 0x733, 0xb33);
        a->f5c = (s16)(((long long)b->fc4 * 0xb33 + 0x800) >> 12);
    } else {
        int t = 1;
        func_02081b64(a, b, 0x99a, 0xe66);
        a->f6c = (b->fc4 << 16) >> 16;
        if (!(b->f7c & 1)) {
            if (b->f7c & 0x402000)
                t = 0;
        }
        a->f24_b3 = (t == 0);
    }
}
