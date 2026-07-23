// PURPOSE: Initializes a normalized direction tracker between two objects.

typedef struct VecFx32 {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct Obj Obj;

typedef struct Source {
    Obj *objA;
    char pad04[0x14];
    VecFx32 *pos;
} Source;

typedef struct Obj {
    char pad00[0x18];
    VecFx32 *pos;
} Obj;

typedef struct Tracker {
    Obj *objA;
    Source *objB;
    VecFx32 vec;
    int f14;
    int f18;
    unsigned short f1c;
} Tracker;

extern const VecFx32 data_021557ec;
extern void VecFx32_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern void Vector3_MaybeNormalize(VecFx32 *a, VecFx32 *b);

void func_0207ffa4(Tracker *t, unsigned short flag, Source *objB)
{
    t->vec = data_021557ec;
    t->objB = objB;
    t->objA = t->objB->objA;
    VecFx32_Subtract(t->objA->pos, t->objB->pos, &t->vec);
    Vector3_MaybeNormalize(&t->vec, &t->vec);
    t->f14 = 0;
    t->f18 = 0;
    t->f1c = flag;
}
