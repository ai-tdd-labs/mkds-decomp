// PURPOSE: Shows a formatted dialog message with either a button or progress display.
// The first argument selects the message text and the second chooses the dialog style.
// The global work data probably supplies formatting values and message archives.

typedef unsigned short u16;
typedef unsigned int u32;

typedef struct DialogWork {
    unsigned char unknown_00[0xa8];
    void *button_message_archive;
    void *prompt_message_archive;
    unsigned char unknown_b0[8];
    u16 format_values[10];
} DialogWork;

extern DialogWork *data_02174e40;

extern void *Bmg_GetRawStringPointer_from_thumb(void *message_archive, int message_id);
extern void CopyMemory16(const void *source, void *destination, u32 size);
extern void MaybeHandleBmgFormatting_from_thumb(void *destination, void *source,
                                                 void *buffer, u32 buffer_size);
extern void TextSystem_DisplaySingleButtonDialog_Simple_from_thumb(void *message,
                                                                     void *button);
extern void TextSystem_DisplayProgressDialog_Simple_from_thumb(void *message);

void func_0202d5f8(int message_id, int show_button)
{
    u16 message[0x10b];
    void *raw_message;

    raw_message = Bmg_GetRawStringPointer_from_thumb(
        data_02174e40->prompt_message_archive, message_id);
    CopyMemory16(data_02174e40->format_values, message, 0x14);
    message[10] = 0;
    MaybeHandleBmgFormatting_from_thumb(message, raw_message, &message[11], 0x100);

    if (show_button != 0) {
        TextSystem_DisplaySingleButtonDialog_Simple_from_thumb(
            &message[11], Bmg_GetRawStringPointer_from_thumb(
                             data_02174e40->button_message_archive, 4));
    } else {
        TextSystem_DisplayProgressDialog_Simple_from_thumb(&message[11]);
    }
}
