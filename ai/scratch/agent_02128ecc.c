// PURPOSE: Shows the keyboard confirmation dialog when the switch is ready.
// Arguments: none.
// It advances the keyboard timer, plays the switch sound, and opens the
// confirmation prompt once the text system is idle. The exact input-state
// fields are probably used to prevent showing the prompt twice.

typedef struct KeyboardScreen {
    unsigned char padding_00[0x10];
    int nextState;
    unsigned char padding_14[0x14];
    int progressDelay;
    unsigned char padding_2c[0x94];
    void *messageArchive;
} KeyboardScreen;

typedef struct KeyboardStatus {
    unsigned char padding_00[0x28];
    unsigned char promptState;
} KeyboardStatus;

typedef struct KeyboardInputState {
    unsigned char padding_00[0xc];
    int field_0c;
    int field_10;
} KeyboardInputState;

extern unsigned char data_0217d068[];
extern KeyboardScreen *gKeyboardScreen;
extern KeyboardInputState *data_0217aa08;
extern KeyboardStatus *data_021759d4;

extern int TextSystem_JustFadedIn_from_thumb(void);
extern void NNSi_MaybeSndPlayerStartSeq(void *player, int playerNo, int sequenceId);
extern int TextSystem_IsDialogIdle_from_thumb(void);
extern void TextSystem_SetFadeInSseqId_from_thumb(int sseqId);
extern void *Bmg_GetRawStringPointer_from_thumb(void *messageArchive, int messageId);
extern void TextSystem_DisplaySingleButtonDialog_from_thumb(
    void *prompt,
    void *button,
    int option3,
    int option4,
    int option5,
    int option6);

void Keyboard_SwitchFn11_from_thumb(void)
{
    int inputState;
    void *prompt;
    void *button;

    if (TextSystem_JustFadedIn_from_thumb()) {
        NNSi_MaybeSndPlayerStartSeq(data_0217d068, 0, 0x22);
    }

    gKeyboardScreen->progressDelay++;

    if (TextSystem_IsDialogIdle_from_thumb() == 0) {
        return;
    }
    if (gKeyboardScreen->progressDelay <= 0x5a) {
        return;
    }

    if (data_021759d4->promptState == 0) {
        if (data_0217aa08->field_0c != 0) {
            inputState = data_0217aa08->field_10;
        } else {
            inputState = 0;
        }
    } else {
        inputState = 1;
    }

    if (inputState != 0) {
        return;
    }

    gKeyboardScreen->nextState = 0xc;
    gKeyboardScreen->progressDelay = 0;
    TextSystem_SetFadeInSseqId_from_thumb(0x21);

    prompt = Bmg_GetRawStringPointer_from_thumb(
        gKeyboardScreen->messageArchive, 9);
    button = Bmg_GetRawStringPointer_from_thumb(
        gKeyboardScreen->messageArchive, 4);
    TextSystem_DisplaySingleButtonDialog_from_thumb(
        prompt, button, 0, 1, 1, 0);
}
