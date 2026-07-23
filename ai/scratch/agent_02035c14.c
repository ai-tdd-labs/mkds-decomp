// PURPOSE: Shows a progress dialog using message number three.
// Arguments: none.
// It probably resets dialog values before showing the message on the top screen.

typedef struct DialogWork {
    unsigned char padding_00[0x88];
    void *messageArchive;
} DialogWork;

extern DialogWork *data_02174e68;

extern void *Bmg_GetRawStringPointer_from_thumb(void *messageArchive, int messageId);
extern void TextSystem_SetSomeValues_from_thumb(int value, int option);
extern void TextSystem_DisplayProgressDialog_TopScreen_from_thumb(
    void *message,
    int option1,
    int option2,
    int option3,
    int option4,
    int option5,
    int option6);

void func_02035c14(void)
{
    void *message;

    message = Bmg_GetRawStringPointer_from_thumb(data_02174e68->messageArchive, 3);
    TextSystem_SetSomeValues_from_thumb(-12, 0);
    TextSystem_DisplayProgressDialog_TopScreen_from_thumb(message, 0, 0, 0, 0, 0, 0);
}
