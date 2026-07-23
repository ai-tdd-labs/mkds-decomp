// PURPOSE: Shows the keyboard progress message after both screens fade in.
// Arguments: none. Once the fade completes, this advances the keyboard state
// and opens progress-dialog message 7 on the top screen.

typedef struct KeyboardScreen {
    unsigned char padding_00[0x10];
    int nextState;
    unsigned char padding_14[0xac];
    void *messageArchive;
} KeyboardScreen;

extern KeyboardScreen *gKeyboardScreen;

extern int Bright_IsBothScreensFadedIn(void);
extern void *Bmg_GetRawStringPointer_from_thumb(void *messageArchive, int messageId);
extern void TextSystem_DisplayProgressDialog_TopScreen_from_thumb(
    void *message,
    int option1,
    int option2,
    int option3,
    int option4,
    int option5,
    int option6);

void Keyboard_SwitchFn0_from_thumb(void)
{
    if (Bright_IsBothScreensFadedIn()) {
        gKeyboardScreen->nextState = 1;
        TextSystem_DisplayProgressDialog_TopScreen_from_thumb(
            Bmg_GetRawStringPointer_from_thumb(gKeyboardScreen->messageArchive, 7),
            0,
            0,
            0,
            0,
            0,
            0);
    }
}
