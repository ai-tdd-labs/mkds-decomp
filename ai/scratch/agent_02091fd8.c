// PURPOSE: Advances the physics/animation timer of every active object in a list.
// Takes a control block (arg0) holding a pointer-array of objects and a count.
// For each non-null object whose flag bit 0x800 is set, it fetches that object's
// 64-bit state block, does one fixed-point step (state = base + rate*state), and
// then writes a small derived value (high word of state scaled by 25, +200) into
// the object's +0xA4 field (probably a countdown/frame counter, clamped to 16 bits).
// Iteration stops early at the first null object pointer.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct Object {
    u16 pad0;           // 0
    u16 flags;          // 2
    u8 pad4[0xA4 - 4];  // 4..0xA3
    u32 field_a4;       // 0xA4: stored as a full word (only low 16 bits meaningful)
} Object;

typedef struct {
    Object **list;      // 0: array of object pointers
    u16 count;          // 4: number of entries
} Ctrl;

// 64-bit state block returned by func_020d22d0 (a small fx64 accumulator)
typedef struct {
    u64 a;              // 0: value (also destination)
    u64 b;              // 8: rate/multiplier
    u64 c;              // 0x10: base/offset
} State;

extern State *func_020d22d0(void);

void func_02091fd8(Ctrl *c)
{
    int i;
    Object *o;

    if (c == 0) return;

    for (i = 0; i < c->count && (o = c->list[i]) != 0; i++) {
        if (o->flags & 0x800) {
            State *s = func_020d22d0();
            s->a = s->c + s->b * s->a;                 // 64-bit multiply-add (low 64)
            o->field_a4 = (u16)((u16)(((u64)(u32)(s->a >> 32) * 25) >> 32) + 0xc8);
        }
    }
}
