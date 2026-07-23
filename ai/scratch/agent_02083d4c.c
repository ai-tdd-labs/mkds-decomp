/* PURPOSE: Starts a new "watcher"/callback object for one racer, replacing any old one.
 *
 * Args: a0 = a source object whose field +4 (probably a state/data pointer) is
 *       what we compare and remember; a1 = a small id/flag byte; a2 = a racer-ish
 *       struct whose u16 at +0x74 selects which entry in the global racer array
 *       (stride 0x58) to operate on.
 * Behaviour: if the entry already remembers this same +4 value, do nothing and
 *   return 0. Otherwise mark the old callback object (if any) as retired (byte
 *   at +0x99 = 1), allocate/build a fresh callback object via func_0208b7bc,
 *   store it plus bookkeeping (a2 at +0x94, a1 at +0x98, a fixed callback
 *   func_02083484 at +0x90) and return 1.
 */

typedef struct Obj {
    char pad90[0x90];
    void (*f90)(void);   /* +0x90 fixed callback */
    void *f94;           /* +0x94 = a2 */
    unsigned char f98;   /* +0x98 = a1 */
    unsigned char f99;   /* +0x99 = retired flag */
} Obj;

typedef struct Entry {
    void *f0;            /* +0x00 remembered a0->f4 */
    char pad4[8];
    Obj *fc;             /* +0x0c current callback object */
    char pad10[0x58 - 0x10];
} Entry;                 /* stride 0x58 */

typedef struct A0 {
    char pad0[4];
    void *f4;            /* +0x04 */
} A0;

typedef struct A2 {
    char pad0[0x74];
    unsigned short f74;  /* +0x74 index */
} A2;

extern Entry *data_0217ae84;      /* base pointer of racer entry array */
extern char data_02155a14[];      /* arg passed to func_0208b7bc */
extern Obj *func_0208b7bc(void *arg, void *ctx);
extern void func_02083484(void);

int func_02083d4c(A0 *a0, int a1, A2 *a2)
{
    Entry *e = &data_0217ae84[a2->f74];
    Obj *p;

    if (a0->f4 == e->f0)
        return 0;

    if (e->fc != 0)
        e->fc->f99 = 1;

    p = func_0208b7bc(a0->f4, data_02155a14);
    e->fc = p;
    e->f0 = a0->f4;
    p->f94 = a2;
    p->f98 = (unsigned char)a1;
    p->f90 = func_02083484;
    return 1;
}
