// PURPOSE: Shows the first confirmation dialog for erasing save data.
// This function takes no arguments and opens a simple two-button prompt.
// It probably loads the logo message archive, then uses message 0x7c with
// its first two button labels.

#define data_021a76a0 ((char *)0x021a76a0)
extern void *FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(char *name);
extern void *Bmg_GetRawStringPointer_from_thumb(void *bmg, int messageId);
extern void TextSystem_DisplayDoubleButtonDialog_Simple_from_thumb(
    void *message, void *leftButton, void *rightButton, int option);

void Logo_StateHandler_AskEraseSaveData_First(void)
{
    void *bmg;
    void *message;
    void *leftButton;
    void *rightButton;

    bmg = FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_021a76a0);
    message = Bmg_GetRawStringPointer_from_thumb(bmg, 0x7c);
    leftButton = Bmg_GetRawStringPointer_from_thumb(bmg, 0);
    rightButton = Bmg_GetRawStringPointer_from_thumb(bmg, 1);
    TextSystem_DisplayDoubleButtonDialog_Simple_from_thumb(
        message, leftButton, rightButton, 1);
}
