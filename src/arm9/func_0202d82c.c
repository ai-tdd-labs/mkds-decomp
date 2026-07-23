// PURPOSE: Shows a simple one-button dialog.
// Arguments: none.
// It obtains the prompt and button labels from the current screen archives.
// The dialog state value is probably the style or mode of this notification.

typedef struct DialogWork {
    unsigned char padding_00[0xa8];
    void *button_message_archive;
    void *prompt_message_archive;
    int dialog_mode;
} DialogWork;

extern DialogWork *data_02174e40;

extern void *Bmg_GetRawStringPointer_from_thumb(void *message_archive, int message_id);
extern void TextSystem_DisplaySingleButtonDialog_Simple_from_thumb(
    void *prompt, void *button_label);

void func_0202d82c(void)
{
    void *prompt;
    void *button_label;

    prompt = Bmg_GetRawStringPointer_from_thumb(
        data_02174e40->prompt_message_archive, 13);
    button_label = Bmg_GetRawStringPointer_from_thumb(
        data_02174e40->button_message_archive, 4);
    data_02174e40->dialog_mode = 8;
    TextSystem_DisplaySingleButtonDialog_Simple_from_thumb(
        prompt, button_label);
}
