// PURPOSE: Enables keyboard character groups according to the entered text length.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct KeyboardCharacter {
    int enabled;
    u8 padding_04[0x3c];
} KeyboardCharacter;

typedef struct KeyboardScreen {
    u8 padding_00[0x04];
    int state;
    u8 padding_08[0x3c];
    u16 text[10];
    u8 padding_58[0x18];
    short inputMode;
    u8 padding_72[0x0a];
    KeyboardCharacter *characters[2];
} KeyboardScreen;

extern KeyboardScreen *gKeyboardScreen;
extern u8 data_0215d0f0[];
extern u32 GetClampedString10LengthForFontIndex0_from_thumb(u16 *string,
                                                            u16 *scratch);

void func_02128b54(void)
{
    u16 scratch[10];
    volatile int disabled;
    volatile int initialColumn;
    int characterCount;
    int firstEnabledRow;
    int row;
    int textLength;

    if (gKeyboardScreen->state == 1) {
        textLength = GetClampedString10LengthForFontIndex0_from_thumb(
            gKeyboardScreen->text, scratch);
        characterCount = 6;
        if (textLength > 4) {
            characterCount = 10 - textLength;
        }

        firstEnabledRow = 6 - characterCount;
        disabled = 0;
        initialColumn = 0;

        for (row = 0; row < 6; row++) {
            int column;

            for (column = initialColumn; column < 2; column++) {
                if (row < firstEnabledRow || gKeyboardScreen->inputMode == 12) {
                    gKeyboardScreen->characters[column]
                        [data_0215d0f0[row]].enabled = disabled;
                } else {
                    gKeyboardScreen->characters[column]
                        [data_0215d0f0[row]].enabled = 1;
                }
            }
        }
    }
}
