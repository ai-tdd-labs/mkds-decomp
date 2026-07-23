/* PURPOSE: Finishes the Wi-Fi help notice and advances the logo screen.
 * This function takes no arguments and returns no value.
 * It closes the notice when any dialog button is pressed.
 * Otherwise, once the dialog finishes, it probably requests logo state 11.
 */

typedef unsigned short u16;

typedef struct LogoStateRequest {
    unsigned char pad_00[0x10];
    u16 nextState;
    u16 requested;
} LogoStateRequest;

typedef struct LogoContext {
    unsigned char pad_00[0x18];
    LogoStateRequest stateRequest;
} LogoContext;

extern int TextSystem_WasAnyDialogButtonPressed_from_thumb(void);
extern int TextSystem_IsDialogFinished_from_thumb(void);
extern void TextSystem_CloseDialog_from_thumb(void);
extern LogoContext *data_ov000_021a99e0;

void Logo_StateHandler_NotifyWiFiHelp_Second(void)
{
    LogoStateRequest *stateRequest;

    if (TextSystem_WasAnyDialogButtonPressed_from_thumb()) {
        TextSystem_CloseDialog_from_thumb();
        return;
    }

    if (!TextSystem_IsDialogFinished_from_thumb()) {
        return;
    }

    stateRequest = &data_ov000_021a99e0->stateRequest;
    stateRequest->nextState = 11;
    stateRequest->requested = 1;
}
