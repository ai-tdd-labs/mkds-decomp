/* PURPOSE: Attaches two helper objects to a racer so the game can track that racer.
 *
 * Arguments: a0 = owner/context object (its field at +4 is passed to the factory),
 *            a1 = a small kind/id byte stored on each helper,
 *            sub = the racer's sub-struct; its u16 at +0x74 indexes the global
 *                  racer-entry array (base *data_0217ae84, stride 0x58).
 * Behaviour: if the racer entry already has either of its two slots (+0x20/+0x24)
 *            filled, do nothing and return 0. Otherwise build 2 helper objects via
 *            func_0208b7bc, store them into the two slots, and fill each helper's
 *            back-pointer (sub), index, kind byte and callback (func_02082fec).
 *            Returns 1 on success.
 */

typedef unsigned char  u8;
typedef unsigned short u16;

/* Helper object produced by the factory. Only the fields written here are known. */
typedef struct Helper {
    u8  pad[0x90];
    void *f90;   /* callback -> func_02082fec */
    void *f94;   /* back-pointer to the racer sub-struct */
    u8  f98;     /* kind byte (a1 & 0xff) */
    u8  pad99[2];
    u8  f9b;     /* slot index (0 or 1) */
} Helper;

/* One entry of the global racer array; stride is 0x58. */
typedef struct RacerEntry {
    u8  pad20[0x20];
    void *slots[2]; /* +0x20, +0x24 */
    u8  pad28[0x58 - 0x28];
} RacerEntry;

/* Owner/context object: only its +4 field is used. */
typedef struct Owner {
    void *pad0;
    void *f4;
} Owner;

/* sub-struct: only the u16 racer index at +0x74 is used. */
typedef struct Sub {
    u8  pad0[0x74];
    u16 f74;
} Sub;

extern RacerEntry *data_0217ae84;      /* pointer to base of racer-entry array */
extern int         data_02155a14;      /* config/data passed to the factory */
extern Helper     *func_0208b7bc(void *a, void *b);
extern void        func_02082fec(void);

int func_02083a24(Owner *a0, int a1, Sub *sub)
{
    RacerEntry *e = &data_0217ae84[sub->f74];
    if (e->slots[0] != 0 || e->slots[1] != 0)
        return 0;

    {
        u16 i = 0;
        for (; i < 2; i++) {
            Helper *o = func_0208b7bc(a0->f4, &data_02155a14);
            data_0217ae84[sub->f74].slots[i] = o;
            o->f94 = sub;
            o->f9b = (u8)i;
            o->f98 = (u8)a1;
            o->f90 = (void *)func_02082fec;
        }
    }
    return 1;
}
