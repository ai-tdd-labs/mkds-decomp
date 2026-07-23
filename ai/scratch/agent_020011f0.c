// PURPOSE: Shows the first Wi-Fi ID problem message.
//
// This reads two messages from the logo screen's archive and opens a simple
// one-button dialog. The shared context layout is only known through the
// message-archive field at offset 0x38.

typedef struct LogoContext {
    unsigned char padding_00[0x38];
    void *messageArchive;
} LogoContext;

#define data_021a99e0 (*(LogoContext **)0x021a99e0)
extern void *Bmg_GetRawStringPointer_from_thumb(void *messageArchive, int messageId);
extern void TextSystem_DisplaySingleButtonDialog_Simple_from_thumb(
    void *message, void *buttonLabel);

void Logo_StateHandler_NotifyWiFiIdIssue_First(void)
{
    void *message;

    message = Bmg_GetRawStringPointer_from_thumb(data_021a99e0->messageArchive, 0x89);
    TextSystem_DisplaySingleButtonDialog_Simple_from_thumb(
        message,
        Bmg_GetRawStringPointer_from_thumb(data_021a99e0->messageArchive, 6));
}
