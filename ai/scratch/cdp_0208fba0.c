/* PURPOSE: Advances a race object one step and decides whether it keeps going
 *          straight ahead or turns/reacts, based on how far it has travelled.
 *
 * Arguments: a (r0) and b (r1) are two game objects passed straight through to
 *   the two follow-up routines. Behaviour:
 *   - If func_0207bfac() says we are in the "active" mode, we fetch a state
 *     block (func_0208537c) and update its 64-bit position:
 *         pos = base + pos * step   (all 64-bit)
 *     Then we look at bits 20.. of the new high word (a signed 16-bit value)
 *     and, if it reached the limit 2867, call func_0207c47c, otherwise
 *     func_0207c548.
 *   - Otherwise we look at counters inside b: bail out early if the first is
 *     zero or the second has passed 90000; if the third is set and the fourth
 *     is above 2867 call func_0207c548, else call func_0207c47c.
 *   Types are best-guess; only the byte-exact behaviour matters here.
 */

typedef unsigned int u32;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned long long u64;

typedef struct {
    u64 pos;    /* 0x0 */
    u64 step;   /* 0x8 */
    u64 base;   /* 0x10 */
} P;

typedef struct {
    char pad[0xb0];
    int f_b0;   /* 0xb0 */
    int f_b4;   /* 0xb4 */
    int f_b8;   /* 0xb8 */
    int f_bc;   /* 0xbc */
} B;

extern int func_0207bfac(void);
extern P *func_0208537c(void);
extern void func_0207c548(void *a, B *b);
extern void func_0207c47c(void *a, B *b);

void func_0208fba0(void *a, B *b)
{
    if (func_0207bfac()) {
        P *p = func_0208537c();
        u32 hi;
        s16 v;

        p->pos = p->base + p->step * p->pos;   /* low 64 bits only */

        hi = (u32)(p->pos >> 32);
        v = (s16)(u16)(hi >> 20);
        if (v < 2867)
            func_0207c548(a, b);
        else
            func_0207c47c(a, b);
    } else {
        if (b->f_b0 == 0)
            return;
        if (b->f_b8 >= 90000)
            return;
        if (b->f_b4 != 0 && b->f_bc > 2867)
            func_0207c548(a, b);
        else
            func_0207c47c(a, b);
    }
}
