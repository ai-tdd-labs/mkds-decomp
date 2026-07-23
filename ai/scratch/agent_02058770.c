// PURPOSE: Resets the active context slot and its status fields.
// This function takes no arguments.
// It probably resets the selected context slot and clears its completion state.

typedef unsigned char u8;
typedef unsigned short u16;

extern u8 *data_0217aa00;
extern void StructTK_SomeFn_from_thumb(void *slot);

void func_02058770(void)
{
    u8 *context = data_0217aa00;
    u16 slotIndex;

    if (*(int *)context == 2) {
        slotIndex = *(u16 *)(context + 0x432);
    } else {
        slotIndex = 0;
    }

    StructTK_SomeFn_from_thumb(context + 0x45c + slotIndex * 0x22c);

    *(u8 *)(data_0217aa00 + 0x1622) |= 1;
    *(u8 *)(data_0217aa00 + 0x1622) = 0;
    *(u16 *)(data_0217aa00 + 0x161e) = 0;
}
