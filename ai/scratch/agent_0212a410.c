// PURPOSE: Copies the keyboard's twelve key values into its byte state list.
// Clears the thirteen-byte state list first, then copies the low byte of each
// probably key-related halfword from the preceding table.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct KeyboardScreen {
    u8 _00[0x2c];
    u8 keyValues[0x18];
    u8 _44[0x18];
    u8 keyStates[0x0d];
} KeyboardScreen;

extern KeyboardScreen *gKeyboardScreen;
extern void Mem_CpuFill8(void *dst, u32 value, u32 size);

void func_0212a410(void)
{
    int i;
    int offset;

    Mem_CpuFill8(gKeyboardScreen->keyStates, 0, 0x0d);

    for (i = 0, offset = 0; i < 12;) {
        /* Read as a halfword while retaining only its low byte. */
        gKeyboardScreen->keyStates[i] = *(u16 *)(gKeyboardScreen->keyValues + offset);
        offset += 2;
        i += 1;
    }
}
