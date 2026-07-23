// PURPOSE: Updates the keyboard dialog state after a dialog finishes.
// Arguments: none.
// It selects the next keyboard state from the focused button, or closes a
// dialog when any button has been pressed before it has finished.

typedef struct KeyboardScreen {
    unsigned char padding_00[0x72];
    unsigned short state;
} KeyboardScreen;

extern KeyboardScreen *gKeyboardScreen;

extern int TextSystem_IsDialogFinished_from_thumb(void);
extern int TextSystem_IsButton2Focused_from_thumb(void);
extern int TextSystem_WasAnyDialogButtonPressed_from_thumb(void);
extern void TextSystem_CloseDialog_from_thumb(void);

void Keyboard_SwitchFn13_from_thumb(void)
{
    if (TextSystem_IsDialogFinished_from_thumb()) {
        if (!TextSystem_IsButton2Focused_from_thumb()) {
            gKeyboardScreen->state = 3;
        } else {
            gKeyboardScreen->state = 0;
        }
    } else if (TextSystem_WasAnyDialogButtonPressed_from_thumb()) {
        TextSystem_CloseDialog_from_thumb();
    }
}
