/* PURPOSE: Shows a progress message after both screens finish fading in.
 * Arguments: none. Once the fade completes, this advances the keyboard state,
 * opens a top-screen progress dialog, and marks that dialog as active.
 * The exact meaning of the two keyboard state fields is uncertain.
 */

typedef struct KeyboardScreen {
    unsigned char padding_00[0x10];
    int nextState;                 /* +0x10 */
    unsigned char padding_14[0x58];
    int progressDialogActive;      /* +0x6c */
    unsigned char padding_70[0x50];
    void *messageArchive;          /* +0xc0 */
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

void Keyboard_SwitchFn5_from_thumb(void)
{
    if (Bright_IsBothScreensFadedIn()) {
        gKeyboardScreen->nextState = 6;
        TextSystem_DisplayProgressDialog_TopScreen_from_thumb(
            Bmg_GetRawStringPointer_from_thumb(gKeyboardScreen->messageArchive, 15),
            0,
            0,
            0,
            0,
            0,
            0);
        gKeyboardScreen->progressDialogActive = 1;
    }
}
