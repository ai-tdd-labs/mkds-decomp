/* PURPOSE: Advances a wobble/bounce timer pair on an object and, once it
 * finishes settling, fires an event describing which of two reference
 * tables the object currently matches.
 *
 * arg0 (unused) is ignored. arg1 is a pointer to the object being updated.
 * The object holds a pair of accumulators (fa4/fa8) that step forward each
 * call; when fa4 wraps back to zero the step is doubled, and once fa4
 * reaches a large threshold the direction/flag (fac) is toggled instead.
 * After the accumulator update, if the object's short field fa2 is zero
 * the function returns early (nothing more to do). Otherwise it checks a
 * "current frame" helper and an associated target's short field; if they
 * differ, or if flag bit 0x4 of f78 is set, it also returns early.
 * Otherwise it classifies the object against a shared config table
 * (data_0217ca6c) by comparing f70 against two of its fields, builds a
 * small event-args struct on the stack, resolves an id via
 * func_020d4ef4, and dispatches the event via func_0210b7a8.
 */

typedef struct {
    unsigned char pad028[0x28];
    short f28; /* probably a frame/state index compared against the "current frame" helper result */
} Target209f6d8;

typedef struct {
    unsigned char pad000[0x70];
    int f70;            /* classification key, compared against data_0217ca6c fields */
    unsigned char pad074[4];
    int f78;            /* flags; bit 0x4 suppresses the event */
    unsigned char pad07c[0x9c - 0x7c];
    Target209f6d8 *f9c;  /* linked target object */
    unsigned char pad0a0[2];
    unsigned short fa2;  /* nonzero while the wobble/settle logic is still active */
    int fa4;             /* accumulator A */
    int fa8;             /* accumulator B / step size */
    int fac;             /* direction/parity flag, toggled at the upper bound */
} Obj209f6d8;

typedef struct {
    unsigned char pad068[0x68];
    int f68; /* classification value 1 */
    unsigned char pad06c[0x8c - 0x6c];
    int f8c; /* classification value 2 */
} ConfigTable209f6d8;

extern ConfigTable209f6d8 data_0217ca6c;

extern int func_0210f744(int a0);
extern int func_020d4ef4(void *addr, int kind);
extern void func_0210b7a8(void *args);

void func_0209f6d8(void *unused0, Obj209f6d8 *self)
{
    self->fa4 = self->fa4 + self->fa8;
    self->fa8 = self->fa8 + 0x4000;

    if (self->fa4 == 0) {
        /* Wrapped exactly to zero: take another step, doubled. */
        self->fa4 = self->fa4 + self->fa8;
        self->fa8 = self->fa8 + 0x4000;
    } else if (self->fa4 >= 0x16c000) {
        /* Reached the upper bound: reverse the step and toggle the flag. */
        self->fa8 = 0x4000 - self->fa8;
        self->fac = (self->fac == 0) ? 1 : 0;
    }

    if (self->fa2 == 0) {
        return;
    }

    if (func_0210f744(0) != self->f9c->f28) {
        return;
    }

    {
        unsigned short kindSrc = self->fa2;

        if (self->f78 & 4) {
            return;
        }

        {
        int kind;

        if (self->f70 == data_0217ca6c.f68) {
            kind = 2;
        } else if (self->f70 == data_0217ca6c.f8c) {
            kind = 3;
        } else {
            kind = 4;
        }

        {
            void *addr = (char *)self + 4;
            int args[4];

            args[0] = kindSrc;
            args[1] = (int)addr;
            args[2] = kind;
            args[3] = func_020d4ef4(addr, kind);

            func_0210b7a8(args);
        }
        }
    }
}
