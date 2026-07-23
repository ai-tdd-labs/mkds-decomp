/*
 * PURPOSE: Advances one racer's map/minimap dot to its next spot and, once
 * it reaches the end, marks that racer finished.
 *
 * Args: o = the racer's tracking object, done = nonzero if already handled
 * (then it returns immediately). Reads the driver's movement deltas from the
 * driver entry (+0x508), scales them down (>>4) and adds them to the object's
 * stored position (+0x28/+0x2c/+0x30). Compares the current step counter
 * (+0x9a) against the target (+0x99): if below target, bump the counter; if
 * equal, set a "reached" flag in +0x24 and clear field +0x30 of the racer's
 * global slot (base[driver*0x58]). Otherwise store the driver's heading
 * (s16 at +0xc4) into +0x6c.
 */

typedef unsigned char u8;

typedef struct {
    int d0;   /* +0x00 */
    int d4;   /* +0x04 */
    int d8;   /* +0x08 */
} Delta;

typedef struct {
    char pad508[0x508];
    Delta *f508;        /* +0x508 */
} DriverEntry;

typedef struct {
    char padc4[0xc4];
    int fc4;           /* +0xc4 (low 16 bits used, sign-extended) */
} DriverEntry2;

typedef struct {
    int pad0;
    int f4;   /* +0x04 */
    int f8;   /* +0x08 */
    int fc;   /* +0x0c */
} Node;

typedef struct {
    Node *node;   /* +0x00 */
} Holder;

typedef struct {
    char pad20[0x20];
    Holder *f20;    /* +0x20 */
    int f24;        /* +0x24 */
    int f28;        /* +0x28 */
    int f2c;        /* +0x2c */
    int f30;        /* +0x30 */
    char pad34[0x6c - 0x34];
    int f6c;        /* +0x6c */
    char pad70[0x99 - 0x70];
    u8 f99;         /* +0x99 */
    u8 f9a;         /* +0x9a */
    u8 f9b;         /* +0x9b */
} Obj;

typedef struct {
    char pad30[0x30];
    int f30;        /* +0x30 */
    char pad34[0x58 - 0x34];
} Slot;             /* size 0x58 */

extern void *GetDriverEntry(int idx);
extern Slot *data_0217ae84;   /* pointer to slot array base */

void func_02081120(Obj *o, int done)
{
    int reached;
    u8 cur;
    u8 drv;

    if (done)
        return;

    drv = o->f9b;
    cur = o->f9a;
    reached = 0;

    {
        Delta *d = ((DriverEntry *)GetDriverEntry(drv))->f508;
        int a = d->d0;
        int b = d->d4;
        int c = d->d8;
        o->f28 = (a >> 4) + o->f20->node->f4;
        o->f2c = o->f20->node->f8 + (b >> 4);
        o->f30 = o->f20->node->fc + (c >> 4);
    }

    if (cur >= o->f99) {
        if (cur == o->f99) {
            reached = 1;
            o->f24 = (o->f24 & ~1) | 1;
        }
    } else {
        o->f9a = cur + 1;
    }

    if (reached) {
        Slot *base = data_0217ae84;
        base[drv].f30 = 0;
    } else {
        int h = ((DriverEntry2 *)GetDriverEntry(drv))->fc4;
        o->f6c = (h << 16) >> 16;
    }
}
