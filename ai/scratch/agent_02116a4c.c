// PURPOSE: Formats a three-part code for display.
// The first argument supplies the three code values.
// The second argument receives five UTF-16 display fields and separators.
// The current system state probably selects the field order and separator style.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct FriendCodeOutput {
    u8 unk_00[4];
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
    u16 unk_0a;
    u16 unk_0c;
    u16 unk_0e;
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
} FriendCodeOutput;

typedef struct FriendCodeState {
    int state;
    int separatorMode;
} FriendCodeState;

extern FriendCodeState *data_021759d0;
extern void func_02116b50(u32 value, u16 *dst);

void func_02116a4c(u8 *code, FriendCodeOutput *output)
{
    FriendCodeState *state = data_021759d0;

    switch (state->state) {
    case 0:
        func_02116b50(0x14, (u16 *)output->unk_00);
        func_02116b50(code[0], &output->unk_04);
        output->unk_08 = 0x2f;
        func_02116b50(code[1], &output->unk_0a);
        output->unk_0e = 0x2f;
        func_02116b50(code[2], &output->unk_10);
        output->unk_14 = 0;
        return;

    case 1:
        func_02116b50(code[1], (u16 *)output->unk_00);
        output->unk_04 = 0x2f;
        func_02116b50(code[2], &output->unk_06);
        output->unk_0a = 0x2f;
        func_02116b50(0x14, &output->unk_0c);
        func_02116b50(code[0], &output->unk_10);
        output->unk_14 = 0;
        return;

    case 2:
        if (state->separatorMode == 3) {
            func_02116b50(code[2], (u16 *)output->unk_00);
            output->unk_04 = 0x2e;
            func_02116b50(code[1], &output->unk_06);
            output->unk_0a = 0x2e;
            func_02116b50(0x14, &output->unk_0c);
            func_02116b50(code[0], &output->unk_10);
            output->unk_14 = 0;
            return;
        }

        func_02116b50(code[2], (u16 *)output->unk_00);
        output->unk_04 = 0x2f;
        func_02116b50(code[1], &output->unk_06);
        output->unk_0a = 0x2f;
        func_02116b50(0x14, &output->unk_0c);
        func_02116b50(code[0], &output->unk_10);
        output->unk_14 = 0;
        return;
    }
}
