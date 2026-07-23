// PURPOSE: Shows the first Wi-Fi help dialog.
// The global work object probably owns the BMG message table at offset 0x38.
// It displays message 0x8a together with message 4 as the button prompt.

typedef struct {
    char pad_00[0x38];
    void *bmg;
} LogoWork;

extern LogoWork *data_021a99e0;
extern void *Bmg_GetRawStringPointer_from_thumb(void *bmg, int message_id);
extern void TextSystem_DisplaySingleButtonDialog_Simple_from_thumb(void *text, void *button);

void Logo_StateHandler_NotifyWiFiHelp_First(void) {
    void *text = Bmg_GetRawStringPointer_from_thumb(data_021a99e0->bmg, 0x8a);

    TextSystem_DisplaySingleButtonDialog_Simple_from_thumb(
        text,
        Bmg_GetRawStringPointer_from_thumb(data_021a99e0->bmg, 4));
}
