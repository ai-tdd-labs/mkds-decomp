// PURPOSE: Sets up an "aim line" that points from one game object toward another
// (e.g. the direction a homing item or camera should look).
// Args: t = the tracker struct to fill in; flag = a small mode value it remembers.
// It fetches two objects from a global manager (t->objA = manager->0xa4, and
// t->objB = objA->0xc), seeds t->vec with a constant, computes the direction
// (objA.pos - objB.pos) into t->vec, normalizes it, then clears two counters and
// stores the flag. probably the constant seed is just overwritten by the subtract.

typedef struct { int x, y, z; } VecFx32;

typedef struct Obj {
    char pad0[0xc];
    struct Obj *f0c;        // 0x0c
    char pad1[0x18 - 0x10];
    VecFx32 *pos;           // 0x18 : pointer to this object's position
} Obj;

typedef struct {
    Obj *objA;              // 0x00
    Obj *objB;              // 0x04
    VecFx32 vec;            // 0x08 : direction (objA.pos - objB.pos), normalized
    int f14;                // 0x14 : counter, cleared to 0
    int f18;                // 0x18 : counter, cleared to 0
    unsigned short f1c;     // 0x1c : the flag argument
    unsigned char f1e;      // 0x1e : cleared to 0
} Tracker;

// bss global manager object, whose pointer lives at 0x02175620. It has no symbol
// in the config (the delinker sees it as data_02175600 + 0x20), so it is referenced
// by absolute address; mwcc keeps the whole address in the pool with an offset-0
// load, exactly matching the ROM. The manager holds the current object at 0xa4.
typedef struct { char pad[0xa4]; Obj *fa4; } Manager;

extern const VecFx32 data_021557ec;
extern void VecFx32_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern void Vector3_MaybeNormalize(VecFx32 *a, VecFx32 *b);

void func_02080d34(Tracker *t, int flag) {
    Manager *mgr = *(Manager **)0x02175620;
    t->objA = mgr->fa4;
    t->objB = t->objA->f0c;              // reload t->objA from memory
    t->vec = data_021557ec;              // seed (overwritten by the subtract)
    VecFx32_Subtract(t->objA->pos, t->objB->pos, &t->vec);
    Vector3_MaybeNormalize(&t->vec, &t->vec);
    t->f14 = 0;
    t->f18 = 0;
    t->f1c = (unsigned short)flag;
    t->f1e = 0;
}
