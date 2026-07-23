/*
 * PURPOSE: Handles the second Wi-Fi ID warning dialog.
 *
 * The function closes the dialog when any button is pressed. If the dialog
 * finishes on its own, it probably advances the logo scene to state 10 and
 * marks that state as newly entered. It takes no arguments and returns no value.
 */

typedef unsigned short u16;

typedef struct LogoStateHandler {
    char padding_00[0x10];
    u16 nextState;
    u16 stateChanged;
} LogoStateHandler;

typedef struct LogoContext {
    char padding_00[0x18];
    LogoStateHandler stateHandler;
} LogoContext;

extern int TextSystem_WasAnyDialogButtonPressed_from_thumb(void);
extern void TextSystem_CloseDialog_from_thumb(void);
extern int TextSystem_IsDialogFinished_from_thumb(void);

void Logo_StateHandler_NotifyWiFiIdIssue_Second(void)
{
    LogoStateHandler *stateHandler;

    if (TextSystem_WasAnyDialogButtonPressed_from_thumb()) {
        TextSystem_CloseDialog_from_thumb();
        return;
    }

    if (!TextSystem_IsDialogFinished_from_thumb()) {
        return;
    }

    /* The relocated pool address has no named symbol in the EUR symbol map. */
    stateHandler = &(*(LogoContext **)0x021a99e0)->stateHandler;
    stateHandler->nextState = 10;
    stateHandler->stateChanged = 1;
}
