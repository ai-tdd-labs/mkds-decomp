// PURPOSE: Releases the object's active resource and clears its handles.
// The argument is probably an object with two related resource fields.
// It does nothing when the primary resource field is absent.
// The exact resource type is not yet known.

typedef struct {
    unsigned char pad00[0x44];
    void *resource;
    void *secondaryResource;
} Object0212C9A4;

extern void func_0212bc20(void *resource);

void func_0212c9a4(Object0212C9A4 *object)
{
    if (object->resource == 0) {
        return;
    }

    func_0212bc20(object->resource);
    object->resource = 0;
    object->secondaryResource = 0;
}
