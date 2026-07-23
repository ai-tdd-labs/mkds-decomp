// PURPOSE: Shows a single-button dialog.
// Arguments: none.
// The message and button label probably describe a dialog state transition.

typedef struct DialogScreenWork {
    unsigned char padding_00[0x84];
    void *buttonMessageArchive;
    void *promptMessageArchive;
    unsigned int padding_8c;
    unsigned int dialogMode;
    unsigned int dialogValue;
} DialogScreenWork;

extern DialogScreenWork *data_02174e64;

extern void *Bmg_GetRawStringPointer_from_thumb(void *messageArchive, int messageId);
extern void TextSystem_SetButtonPressSseqId_from_thumb(int button, int sseqId);
extern void TextSystem_DisplaySingleButtonDialog_Simple_from_thumb(
    void *prompt, void *buttonLabel);

void func_020353a4(void)
{
    void *prompt;
    void *buttonLabel;

    prompt = Bmg_GetRawStringPointer_from_thumb(data_02174e64->promptMessageArchive, 0x11);
    buttonLabel = Bmg_GetRawStringPointer_from_thumb(data_02174e64->buttonMessageArchive, 4);
    TextSystem_SetButtonPressSseqId_from_thumb(0, 5);
    TextSystem_DisplaySingleButtonDialog_Simple_from_thumb(prompt, buttonLabel);
    data_02174e64->dialogMode = 0;
    data_02174e64->dialogValue = 0xf;
}
