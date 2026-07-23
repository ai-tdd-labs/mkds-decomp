/* PURPOSE: Starts erasing save data and shows its progress message.
 * This function takes no arguments and returns no value.
 * It replaces the empty save, then probably opens message 0x7e when the
 * logo context requests visible progress and clears the dialog-active field.
 */

typedef struct LogoContext {
    unsigned char padding_00[0x2c];
    signed int showEraseProgress : 1; /* +0x2c, exact meaning uncertain */
    unsigned int paddingBits : 31;
    unsigned char padding_30[4];
    int progressDialogActive;          /* +0x34 */
    void *messageArchive;              /* +0x38 */
} LogoContext;

extern void OverwriteEmptySaveData_from_thumb(void);
extern void *Bmg_GetRawStringPointer_from_thumb(void *messageArchive, int messageId);
extern void TextSystem_DisplayProgressDialog_from_thumb(
    void *message,
    int option1,
    int option2,
    int option3,
    int option4,
    int option5);

void Logo_StateHandler_EraseSaveData_First(void)
{
    LogoContext *logoContext;

    OverwriteEmptySaveData_from_thumb();

    /* This relocated overlay pointer has no name in the EUR symbol map. */
    logoContext = *(LogoContext **)0x021a99e0;
    if (!logoContext->showEraseProgress) {
        return;
    }

    TextSystem_DisplayProgressDialog_from_thumb(
        Bmg_GetRawStringPointer_from_thumb(logoContext->messageArchive, 0x7e),
        1,
        1,
        1,
        0,
        1);

    /* Reload the shared context because the calls may replace it. */
    (*(LogoContext **)0x021a99e0)->progressDialogActive = 0;
}
