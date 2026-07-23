/* PURPOSE: Updates a kart's on-screen position/state from its racing-line
 * progress, but only once per frame (skips when the "already done" flag is set).
 *
 * arg0 (obj): the kart/racer object.
 * arg1 (skip): if non-zero, do nothing and return immediately.
 * Looks up this racer's driver entry (via checkpoint indices at +0x9b/+0x9a),
 * reads three position deltas (>>4) from a shared path table and stores the
 * resulting coordinates into the object at +0x28/+0x2c/+0x30, copies three
 * words of extra data into +0x40, then advances or latches the checkpoint
 * counter at +0x9a depending on how it compares to the target at +0x99.
 */

typedef struct Vec3 { int a, b, c; } Vec3;

typedef struct DriverEntry {
    char pad[0x3b0];
    Vec3 f3b0;      /* three words copied into obj+0x40 */
    char pad2[0x508 - 0x3bc];
    int *f508;      /* pointer to path node: {f0, f4, f8} */
} DriverEntry;

extern DriverEntry *GetDriverEntry(int a);

typedef struct Racer {
    char pad20[0x20];
    int **f20;      /* +0x20: pointer to struct {..,f4,f8,fc} */
    int f24;        /* +0x24 */
    int f28;        /* +0x28 */
    int f2c;        /* +0x2c */
    int f30;        /* +0x30 */
    char pad34[0x40 - 0x34];
    Vec3 f40;       /* +0x40 */
    char pad4c[0x99 - 0x4c];
    unsigned char f99;  /* +0x99 target */
    unsigned char f9a;  /* +0x9a counter */
    unsigned char f9b;  /* +0x9b */
} Racer;

void func_02081d78(Racer *obj, int skip)
{
    DriverEntry *de;
    int *node;
    int n0, n1, n2;
    unsigned char cur;

    if (skip)
        return;

    cur = obj->f9a;                 /* preloaded, kept in r4 for later compare */
    de = GetDriverEntry(obj->f9b);
    node = de->f508;
    n0 = node[0];                   /* three deltas loaded up front */
    n1 = node[1];
    n2 = node[2];

    obj->f28 = (n0 >> 4) + (*obj->f20)[1];
    obj->f2c = (*obj->f20)[2] + (n1 >> 4);
    obj->f30 = (*obj->f20)[3] + (n2 >> 4);

    obj->f40 = de->f3b0;            /* 3-word block copy (ldm/stm) */

    if (cur >= obj->f99) {
        if (cur == obj->f99)
            obj->f24 = (obj->f24 & ~1) | 1;
    } else {
        obj->f9a = cur + 1;
    }
}
