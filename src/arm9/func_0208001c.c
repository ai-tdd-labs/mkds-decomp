// PURPOSE: Records how far an object moved since last frame and, if it moved far
// enough, turns that movement into a normalized direction vector.
// Args: s = a tracker struct; newObj = the object's current state.
// It remembers the previous object, stores the current one, computes the
// position delta (current - previous) into s->vec, and if the delta's squared
// length is >= 0x10 it normalizes s->vec; otherwise it leaves it alone.

typedef struct { int x, y, z; } VecFx32;

typedef struct Obj {
    char pad[0x20];
    VecFx32 *pos;  // pointer at 0x20
} Obj;

typedef struct {
    Obj *cur;      // 0x00
    Obj *prev;     // 0x04
    VecFx32 vec;   // 0x08
} State;

extern const VecFx32 data_021557ec;
extern void VecFx32_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern void Vector3_MaybeNormalize(VecFx32 *a, VecFx32 *b);

void func_0208001c(State *s, Obj *newObj) {
    s->prev = s->cur;
    s->cur = newObj;
    s->vec = data_021557ec;
    VecFx32_Subtract(s->cur->pos, s->prev->pos, &s->vec);
    // squared magnitude; ROM loads y,x,z in that order (first two swapped)
    if ((long long)s->vec.x * s->vec.x
        + (long long)s->vec.y * s->vec.y
        + (long long)s->vec.z * s->vec.z < 0x10)
        return;
    Vector3_MaybeNormalize(&s->vec, &s->vec);
}
