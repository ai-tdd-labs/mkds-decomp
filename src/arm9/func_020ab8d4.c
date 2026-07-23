// PURPOSE: Updates the keyboard selection rectangle from four supplied values.
// The values are stored in the shared keyboard state and combined with its base coordinates.
// The final call probably applies the resulting rectangle to the keyboard renderer.

typedef unsigned int u32;

typedef struct Global78 {
    unsigned char pad_00[0x50];
    u32 keyValue0;
    u32 keyValue1;
    u32 keyValue2;
    u32 keyValue3;
    u32 keyValue4;
    u32 keyValue5;
    u32 keyValue6;
    u32 keyValue7;
    u32 keyValue8;
    u32 keyValue9;
} Global78;

extern Global78 *data_0217b334;
extern void func_020a9ed8(u32 arg0, u32 arg1, u32 arg2, u32 arg3);

void func_020ab8d4(u32 arg0, u32 arg1, u32 arg2, u32 arg3)
{
    Global78 *state;

    data_0217b334->keyValue6 = arg0;
    data_0217b334->keyValue7 = arg1;
    data_0217b334->keyValue8 = arg2;
    data_0217b334->keyValue9 = arg3;

    state = data_0217b334;
    func_020a9ed8(state->keyValue0 + state->keyValue6,
                  state->keyValue1 + state->keyValue7,
                  state->keyValue0 + state->keyValue8,
                  state->keyValue1 + state->keyValue9);
}
