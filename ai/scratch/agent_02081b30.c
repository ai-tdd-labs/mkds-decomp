// PURPOSE: Updates an object from its driver's entry when the mode is zero.
// Takes an object and a mode flag.
// If the mode is nonzero, the object is left unchanged.
// The byte at 0x9b probably selects the driver's data entry.

typedef struct Foo {
    unsigned char pad_00[0x94];
    int mode;
    unsigned char pad_98[3];
    unsigned char driver_id;
} Foo;

typedef struct Bar Bar;

extern Bar *GetDriverEntry(int driver_id);
extern void func_02081ca0(Foo *a, Bar *b, int mode);

void func_02081b30(Foo *a, int enabled)
{
    if (enabled != 0) {
        return;
    }

    func_02081ca0(a, GetDriverEntry(a->driver_id), a->mode);
}
