// PURPOSE: Animates the keyboard switch indicators before advancing the screen state.

typedef struct KeyboardScreen {
    unsigned char padding_00[0x10];
    int nextState;
    unsigned char padding_14[0x14];
    int progressDelay;
    unsigned char padding_2c[0x5a];
    short indicatorA;
    unsigned char padding_88[2];
    short indicatorB;
} KeyboardScreen;

extern KeyboardScreen *gKeyboardScreen;
extern short data_0215d100[];
extern short data_0215d108[];

extern int ComputeValueInterpolation_from_thumb(int, int, int, int, int);
extern int TextSystem_IsDialogIdle_from_thumb(void);

void Keyboard_SwitchFn9_from_thumb(void)
{
    int bottom;

    gKeyboardScreen->progressDelay++;
    bottom = data_0215d100[2];
    gKeyboardScreen->indicatorA = ComputeValueInterpolation_from_thumb(
        1, data_0215d100[0], data_0215d100[0] - (0xc0 - bottom),
        gKeyboardScreen->progressDelay, 15);
    gKeyboardScreen->indicatorB = ComputeValueInterpolation_from_thumb(
        1, data_0215d108[2], bottom, gKeyboardScreen->progressDelay, 15);

    if (gKeyboardScreen->progressDelay >= 15) {
        gKeyboardScreen->progressDelay = 15;
    }

    if (gKeyboardScreen->progressDelay >= 15) {
        if (TextSystem_IsDialogIdle_from_thumb()) {
            gKeyboardScreen->nextState = 10;
            gKeyboardScreen->progressDelay = 0;
        }
    }
}
