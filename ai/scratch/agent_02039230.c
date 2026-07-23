// PURPOSE: Reads pending controller input and reports the pressed buttons.
// This probably consumes one queued input record when the input mode is one.
// It returns zero when the queue has no complete record, otherwise a button mask.
// The final call probably advances or acknowledges the input source.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct InputState {
    u8 *unknown0;
    u32 limit;
    u8 *data;
    u8 unknown0c[8];
    u32 remaining;
    u16 unknown18;
} InputState;

extern InputState *data_021755c0;
extern void func_02039378(int, int);

int GetSomeInput(void)
{
    InputState *input = data_021755c0;
    u8 *data = input->data;
    u32 limit = input->limit;
    u32 remaining = input->remaining;
    u32 buttons;

    if (data + remaining > (u8 *)limit) {
        return 0;
    }

    if (remaining == 1) {
        u8 value = *data;
        u32 mask = input->unknown18;
        u32 bit = 1;
        u16 shifted = 1;

        buttons = 0;
        do {
            if ((bit & value) != 0) {
                buttons |= shifted;
            }
            bit = (bit << 1) & 0xff;
            if (bit == 0) {
                break;
            }
            shifted <<= 1;
        } while (shifted < 0x10000);
    } else {
        buttons = *(u16 *)data;
    }

    func_02039378(1, 1);
    return buttons;
}
