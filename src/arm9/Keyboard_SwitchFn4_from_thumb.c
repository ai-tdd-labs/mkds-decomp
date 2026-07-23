/* PURPOSE: Shows a connection progress message after a short delay.
 * Arguments: none. This advances a keyboard-screen timer, plays sequence 0x15
 * when the text system finishes fading in, and opens message 7 after 120 ticks.
 * The exact purpose of the sequence and keyboard state value is uncertain.
 */

typedef struct KeyboardScreen {
    unsigned char padding_00[0x10];
    int nextState;                 /* +0x10 */
    unsigned char padding_14[0x14];
    int progressDelay;             /* +0x28 */
    unsigned char padding_2c[0x94];
    void *messageArchive;          /* +0xc0 */
} KeyboardScreen;

extern KeyboardScreen *gKeyboardScreen;
extern unsigned char data_0217d068[];

extern int TextSystem_JustFadedIn_from_thumb(void);
extern void NNSi_MaybeSndPlayerStartSeq(void *player, int playerNo, int sequenceId);
extern void *Bmg_GetRawStringPointer_from_thumb(void *messageArchive, int messageId);
extern void TextSystem_DisplayProgressDialog_TopScreen_from_thumb(
    void *message,
    int option1,
    int option2,
    int option3,
    int option4,
    int option5,
    int option6);

void Keyboard_SwitchFn4_from_thumb(void)
{
    gKeyboardScreen->progressDelay++;

    if (TextSystem_JustFadedIn_from_thumb()) {
        NNSi_MaybeSndPlayerStartSeq(data_0217d068, 0, 0x15);
    }

    if (gKeyboardScreen->progressDelay >= 120) {
        gKeyboardScreen->nextState = 1;
        TextSystem_DisplayProgressDialog_TopScreen_from_thumb(
            Bmg_GetRawStringPointer_from_thumb(gKeyboardScreen->messageArchive, 7),
            0,
            0,
            0,
            0,
            0,
            0);
        gKeyboardScreen->progressDelay = 0;
    }
}
