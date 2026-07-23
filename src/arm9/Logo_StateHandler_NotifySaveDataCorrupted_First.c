// PURPOSE: Shows the two-part warning when save data is corrupted.
// The shared message database probably lives through data_021a99e0.
// It retrieves messages 0x7d and 4, then opens a simple single-button dialog.

typedef struct BmgHolder {
    char pad[0x38];
    void *bmg;
} BmgHolder;

#define data_021a99e0 (*(BmgHolder **)0x021a99e0)
extern void *Bmg_GetRawStringPointer_from_thumb(void *bmg, int id);
extern void TextSystem_DisplaySingleButtonDialog_Simple_from_thumb(void *text, void *button_text);

void Logo_StateHandler_NotifySaveDataCorrupted_First(void) {
    void *text = Bmg_GetRawStringPointer_from_thumb(data_021a99e0->bmg, 0x7d);
    TextSystem_DisplaySingleButtonDialog_Simple_from_thumb(
        text, Bmg_GetRawStringPointer_from_thumb(data_021a99e0->bmg, 4));
}
