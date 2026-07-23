/* PURPOSE: Advances one racer's scrolled screen position and ticks its
   spawn/place counter each frame.
   obj  = the racer/entity object (r0).
   skip = if nonzero, do nothing this frame (r1).
   Reads a shared base pointer (obj->f20) plus this racer's delta vector
   (from its driver-table entry) and writes the three scrolled coords
   (0x28/0x2c/0x30 = base + delta>>4). Then it either bumps a small
   progress counter (0x9a) while it is below the target (0x99), or, once
   it reaches the target exactly, sets a "done" flag bit in obj->f24.
   The base pointer is re-read for every coord (aliasing), so it is not
   cached in a local. */

typedef struct { int f0, f4, f8, fc; } Vec;
typedef struct { int x, y, z; } Delta;              /* delta at entry+0x508 */
typedef struct { char _pad[0x508]; Delta *d; } DriverEntry;

typedef struct {
    char _pad0[0x20];
    Vec **f20;              /* 0x20: pointer to shared base-vector pointer */
    unsigned int f24 : 1;   /* 0x24 bit0: done flag */
    unsigned int f24_rest : 31;
    int f28;               /* 0x28: scrolled X */
    int f2c;               /* 0x2c: scrolled Y */
    int f30;               /* 0x30: scrolled Z */
    char _pad34[0x99 - 0x34];
    unsigned char f99;     /* 0x99: target count */
    unsigned char f9a;     /* 0x9a: current count */
    unsigned char f9b;     /* 0x9b: driver id */
} Obj;

extern DriverEntry *GetDriverEntry(int id);

void func_02081e5c(Obj *obj, int skip) {
    DriverEntry *entry;
    Delta *d;
    int dx, dy, dz;                 /* hoisted up-front (eager load) */
    unsigned char a, b, lim;

    if (skip) return;

    b = obj->f9b;
    a = obj->f9a;                   /* survives the call -> callee-saved */
    entry = GetDriverEntry(b);
    d = entry->d;
    dx = d->x;
    dy = d->y;
    dz = d->z;

    obj->f28 = (dx >> 4) + (*obj->f20)->f4;   /* operand order -> base=r0,dx=r1 */
    obj->f2c = (*obj->f20)->f8 + (dy >> 4);
    obj->f30 = (*obj->f20)->fc + (dz >> 4);

    lim = obj->f99;
    if ((unsigned int)a < lim) goto bump;   /* real blo to duplicated tail */
    if (a == lim) {
        obj->f24 = 1;              /* bitfield set -> bic #1 ; orr #1 */
    }
    return;
bump:
    obj->f9a = a + 1;
}
