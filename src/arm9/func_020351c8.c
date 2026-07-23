/* PURPOSE: Shows a confirmation dialog with two choices.
 * Arguments: none.
 * The dialog prompt comes from one message archive, while both button labels
 * come from another. The exact meaning of the choices is uncertain.
 */

typedef struct DialogScreenWork {
    unsigned char padding_00[0x84];
    void *buttonMessageArchive;
    void *promptMessageArchive;
} DialogScreenWork;

extern DialogScreenWork *data_02174e64;

extern void *Bmg_GetRawStringPointer_from_thumb(void *messageArchive, int messageId);
extern void TextSystem_SetButtonPressSseqId_from_thumb(int button, int sseqId);
extern void TextSystem_DisplayDoubleButtonDialog_from_thumb(
    void *prompt,
    void *leftButtonLabel,
    void *rightButtonLabel,
    int option3,
    int option4,
    int option5,
    int option6,
    int option7);

void func_020351c8(void)
{
    void *prompt;
    void *leftButtonLabel;
    void *rightButtonLabel;

    prompt = Bmg_GetRawStringPointer_from_thumb(data_02174e64->promptMessageArchive, 8);
    leftButtonLabel = Bmg_GetRawStringPointer_from_thumb(data_02174e64->buttonMessageArchive, 0);
    rightButtonLabel = Bmg_GetRawStringPointer_from_thumb(data_02174e64->buttonMessageArchive, 1);

    TextSystem_SetButtonPressSseqId_from_thumb(0, 5);
    TextSystem_DisplayDoubleButtonDialog_from_thumb(
        prompt, leftButtonLabel, rightButtonLabel, 0, 0, 1, 1, 0);
}
