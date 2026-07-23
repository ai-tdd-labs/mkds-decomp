// PURPOSE: When a kart's list of "things to show" changes, refreshes the on-screen
// objects for that racer so the display matches the new list.
// Args: a = list of item-ids (u16 count at +0, then u32 ids from +4),
//       arg1 = unused, b = racer/context object (its racer-slot index is at +0x74).
// For each slot i whose stored id differs from a->ids[i]: tells the two old
// display objects (pointers at entry+i*8+0x10/0x14) they are stale (byte +0x99=1),
// writes the new id, then builds 2 fresh display objects via func_0208b7bc and
// stores them back. Returns 0 if the list is empty, else 1.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    char pad0[0x90];
    void *f90;   // 0x90: callback/vtable = func_0208335c
    void *f94;   // 0x94: owner context b
    char pad98;
    u8   f99;    // 0x99: "stale" flag
    char pad9a;
    u8   f9b;    // 0x9b: slot sub-index j
} Obj;

typedef struct {
    u16 count;   // 0x00
    u32 ids[1];  // 0x04
} IdList;

extern u8 *data_0217ae84;                 // -> base of racer-entry array, stride 0x58
extern u8 data_02155a14[];                // param passed to func_0208b7bc
extern void func_0208335c(void);          // callback stored at obj+0x90
extern Obj *func_0208b7bc(u32 id, u8 *ctx);

int func_02083c18(IdList *a, int arg1, void *b) {
    unsigned short i = 0;
    volatile int result;

    /* All callee-saved locals hoisted to function scope; declaration order
       tunes mwcc coloring (reverse-decl: last declared -> lowest reg).
       Want rp=r4, cb=r5, i8=r6, slot=r7, j=r8, ctx=fp. */
    u8 *ctx;      /* fp */
    unsigned short j;
    u8 *slot;     /* r7 */
    void *cb;     /* r5 */
    u32 i8;       /* r6 */

    if (!((u32)i < a->count))
        return 0;

    ctx = data_02155a14;
    cb = (void *)func_0208335c;
    result = 1;
    do {
        u8 *entry = data_0217ae84 + *(u16 *)((u8 *)b + 0x74) * 0x58;
        j = 0;   /* ROM reloads j-init (spilled 0) at the top of each outer pass */
        if (*(u32 *)((u8 *)a + ((u32)i << 2) + 4)
                != *(u32 *)(entry + ((u32)i << 2) + 4)) {
            Obj *o;
            slot = entry + ((u32)i << 2);    /* ROM r7: kept across inner loop */
            i8 = (u32)i << 3;                /* ROM r6: kept across inner loop */

            o = *(Obj **)(entry + i8 + 0x10);
            if (o) o->f99 = (u8)result;
            o = *(Obj **)(entry + i8 + 0x14);
            if (o) o->f99 = (u8)result;

            *(u32 *)(slot + 4) = *(u32 *)((u8 *)a + ((u32)i << 2) + 4);

            do {
                Obj *p = func_0208b7bc(*(u32 *)(slot + 4), ctx);
                *(Obj **)(data_0217ae84 + *(u16 *)((u8 *)b + 0x74) * 0x58
                          + i8 + ((u32)j << 2) + 0x10) = p;
                p->f94 = b;
                p->f9b = (u8)j;
                p->f90 = cb;
            } while (++j < 2);
        }
    } while (++i < a->count);
    return result;
}
