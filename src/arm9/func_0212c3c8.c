// PURPOSE: Sends a sound command for the current object.
// The first argument points to a probably optional object pointer.
// Its byte at offset 0x3c is sent with the two remaining arguments.
// Returns whether a command was sent.

typedef struct MaybeObject {
    unsigned char pad_0x00[0x3c];
    unsigned char sound_value;
} MaybeObject;

extern void func_02020d34(int value0, int value1, int value2);

int func_0212c3c8(MaybeObject **object, int value1, int value2)
{
    if (*object == 0) {
        return 0;
    }

    func_02020d34((*object)->sound_value, value1, value2);
    return 1;
}
