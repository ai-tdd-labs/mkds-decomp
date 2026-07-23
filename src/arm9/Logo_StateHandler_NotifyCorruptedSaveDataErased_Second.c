/* PURPOSE: Finishes the erased-corrupted-save notice and advances the logo screen.
 * This function takes no arguments and returns no value.
 * It closes the notice with a sound when any dialog button is pressed.
 * Otherwise, once the dialog finishes, it probably requests logo state 8.
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
extern void TextSystem_SetFadeInSseqId_from_thumb(int sseqId);
extern void TextSystem_CloseDialog_from_thumb(void);
extern int TextSystem_IsDialogFinished_from_thumb(void);

void Logo_StateHandler_NotifyCorruptedSaveDataErased_Second(void)
{
    LogoStateRequest *stateRequest;

    if (TextSystem_WasAnyDialogButtonPressed_from_thumb()) {
        TextSystem_SetFadeInSseqId_from_thumb(0x23);
        TextSystem_CloseDialog_from_thumb();
        return;
    }

    if (!TextSystem_IsDialogFinished_from_thumb()) {
        return;
    }

    /* This relocated overlay pointer has no name in the EUR symbol map. */
    stateRequest = &(*(LogoContext **)0x021a99e0)->stateRequest;
    stateRequest->nextState = 8;
    stateRequest->requested = 1;
}
