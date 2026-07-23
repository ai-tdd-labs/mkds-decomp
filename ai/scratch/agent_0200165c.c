// PURPOSE: Shows the message after corrupted save data is erased.
// Sets the dialog fade-in sound, then fetches the two button-dialog strings.
// The shared global probably owns the BMG resource at offset 0x38.

#define data_021a99e0 (*(void **)0x021a99e0)

extern void TextSystem_SetFadeInSseqId_from_thumb(int sseqId);
extern void *Bmg_GetRawStringPointer_from_thumb(void *bmg, int stringId);
extern void TextSystem_DisplaySingleButtonDialog_Simple_from_thumb(void *message, void *button);

void Logo_StateHandler_NotifyCorruptedSaveDataErased_First(void)
{
    void *message;

    TextSystem_SetFadeInSseqId_from_thumb(0x21);
    message = Bmg_GetRawStringPointer_from_thumb(*(void **)((char *)data_021a99e0 + 0x38), 0x80);
    TextSystem_DisplaySingleButtonDialog_Simple_from_thumb(
        message,
        Bmg_GetRawStringPointer_from_thumb(*(void **)((char *)data_021a99e0 + 0x38), 4));
}
