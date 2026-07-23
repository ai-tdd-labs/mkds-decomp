// PURPOSE: Updates an object's driver state when its mode is zero.
// The object and a mode flag are passed as arguments.
// It loads the selected driver entry, applies the object's configured mode,
// and then advances or marks its small progress counter.

typedef struct Foo {
    unsigned char pad_00[0x24];
    int flags;
    unsigned char pad_28[0x94 - 0x28];
    int mode;
    unsigned char pad_98;
    unsigned char target;
    unsigned char current;
    unsigned char driver_id;
} Foo;

typedef struct Bar Bar;

extern Bar *GetDriverEntry(int driver_id);
extern void func_02081ca0(Foo *a, Bar *b, int mode);

void func_02081ab8(Foo *a, int enabled)
{
    unsigned char current;

    if (enabled != 0)
        return;

    current = a->current;
    func_02081ca0(a, GetDriverEntry(a->driver_id), a->mode);

    if (current >= a->target) {
        if (current == a->target)
            a->flags = (a->flags & ~1) | 1;
    } else {
        a->current = current + 1;
    }
}
