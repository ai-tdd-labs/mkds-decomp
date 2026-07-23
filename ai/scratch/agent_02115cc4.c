// PURPOSE: Closes the current dialog and sets its button sound.
// This function takes no arguments.
// It probably finishes a dialog state by updating two fields in its global work.

typedef struct DialogWork {
    unsigned char padding_00[0x58];
    int field_58;
    int field_5c;
} DialogWork;

extern DialogWork *data_0217d350;
extern void TextSystem_CloseDialog_from_thumb(void);
extern void TextSystem_SetButtonPressSseqId_from_thumb(int button, int sseqId);

void func_02115cc4(void)
{
    data_0217d350->field_58 = 10;
    data_0217d350->field_5c = 0;
    TextSystem_CloseDialog_from_thumb();
    TextSystem_SetButtonPressSseqId_from_thumb(0, 5);
}
